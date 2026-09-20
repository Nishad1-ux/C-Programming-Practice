/*
    ADVANCED C CPU RAY TRACER
    --------------------------
    Compile:
        gcc raytracer.c -O3 -lm -lpthread -o raytracer

    Run:
        ./raytracer

    Output:
        render.ppm

    Open render.ppm with any image viewer that supports PPM.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include <stdint.h>
#include <time.h>

#define WIDTH       1920
#define HEIGHT      1080

#define SAMPLES     16
#define MAX_DEPTH   8

#define NUM_THREADS 8
#define NUM_SPHERES 7
#define NUM_LIGHTS  3

#define PI 3.14159265358979323846

/* ============================================================
                         VECTOR
   ============================================================ */

typedef struct {
    double x, y, z;
} Vec3;

static Vec3 v3(double x, double y, double z)
{
    return (Vec3){x, y, z};
}

static Vec3 add(Vec3 a, Vec3 b)
{
    return v3(a.x+b.x, a.y+b.y, a.z+b.z);
}

static Vec3 sub(Vec3 a, Vec3 b)
{
    return v3(a.x-b.x, a.y-b.y, a.z-b.z);
}

static Vec3 mul(Vec3 a, double s)
{
    return v3(a.x*s, a.y*s, a.z*s);
}

static Vec3 hadamard(Vec3 a, Vec3 b)
{
    return v3(a.x*b.x, a.y*b.y, a.z*b.z);
}

static double dot(Vec3 a, Vec3 b)
{
    return a.x*b.x + a.y*b.y + a.z*b.z;
}

static Vec3 cross(Vec3 a, Vec3 b)
{
    return v3(
        a.y*b.z - a.z*b.y,
        a.z*b.x - a.x*b.z,
        a.x*b.y - a.y*b.x
    );
}

static double length3(Vec3 a)
{
    return sqrt(dot(a,a));
}

static Vec3 normalize(Vec3 a)
{
    double l = length3(a);

    if (l < 1e-12)
        return v3(0,0,0);

    return mul(a, 1.0/l);
}

static Vec3 reflect(Vec3 incident, Vec3 normal)
{
    return sub(incident, mul(normal, 2.0 * dot(incident, normal)));
}

static Vec3 clamp3(Vec3 a, double lo, double hi)
{
    double x = a.x < lo ? lo : (a.x > hi ? hi : a.x);
    double y = a.y < lo ? lo : (a.y > hi ? hi : a.y);
    double z = a.z < lo ? lo : (a.z > hi ? hi : a.z);

    return v3(x,y,z);
}

/* ============================================================
                         RANDOM
   ============================================================ */

typedef struct {
    uint64_t state;
} RNG;

static uint64_t rng_next(RNG *r)
{
    uint64_t x = r->state;

    x ^= x >> 12;
    x ^= x << 25;
    x ^= x >> 27;

    r->state = x;

    return x * 2685821657736338717ULL;
}

static double random01(RNG *r)
{
    return (rng_next(r) >> 11) * (1.0 / 9007199254740992.0);
}

/* ============================================================
                         RAY
   ============================================================ */

typedef struct {
    Vec3 origin;
    Vec3 direction;
} Ray;

/* ============================================================
                         MATERIAL
   ============================================================ */

typedef struct {
    Vec3 color;

    double ambient;
    double diffuse;
    double specular;

    double shininess;
    double reflection;
} Material;

/* ============================================================
                         OBJECTS
   ============================================================ */

typedef enum {
    SPHERE,
    PLANE
} ObjectType;

typedef struct {
    ObjectType type;

    Vec3 position;
    double radius;

    Vec3 normal;

    Material material;
} Object;

/* ============================================================
                         LIGHT
   ============================================================ */

typedef struct {
    Vec3 position;
    Vec3 color;

    double intensity;
} Light;

/* ============================================================
                         HIT
   ============================================================ */

typedef struct {
    double distance;

    Vec3 point;
    Vec3 normal;

    Material material;

    int hit;
} Hit;

/* ============================================================
                         SCENE
   ============================================================ */

static Object spheres[NUM_SPHERES];
static Light lights[NUM_LIGHTS];

/* ============================================================
                         CAMERA
   ============================================================ */

typedef struct {
    Vec3 position;

    Vec3 forward;
    Vec3 right;
    Vec3 up;

    double fov;
} Camera;

static Camera camera;

/* ============================================================
                      INTERSECTIONS
   ============================================================ */

static int intersect_sphere(
    Ray ray,
    Object *obj,
    Hit *hit
)
{
    Vec3 oc = sub(ray.origin, obj->position);

    double a = dot(ray.direction, ray.direction);
    double b = 2.0 * dot(oc, ray.direction);
    double c = dot(oc,oc) - obj->radius * obj->radius;

    double discriminant = b*b - 4*a*c;

    if (discriminant < 0)
        return 0;

    double s = sqrt(discriminant);

    double t1 = (-b - s) / (2*a);
    double t2 = (-b + s) / (2*a);

    double t = t1;

    if (t < 0.001)
        t = t2;

    if (t < 0.001)
        return 0;

    if (t >= hit->distance)
        return 0;

    hit->distance = t;
    hit->point = add(
        ray.origin,
        mul(ray.direction, t)
    );

    hit->normal = normalize(
        sub(hit->point, obj->position)
    );

    hit->material = obj->material;
    hit->hit = 1;

    return 1;
}

static int intersect_plane(
    Ray ray,
    Object *obj,
    Hit *hit
)
{
    double denominator = dot(ray.direction, obj->normal);

    if (fabs(denominator) < 1e-8)
        return 0;

    double t = dot(
        sub(obj->position, ray.origin),
        obj->normal
    ) / denominator;

    if (t < 0.001 || t >= hit->distance)
        return 0;

    hit->distance = t;

    hit->point = add(
        ray.origin,
        mul(ray.direction, t)
    );

    hit->normal = obj->normal;

    hit->material = obj->material;
    hit->hit = 1;

    return 1;
}

/* ============================================================
                       SCENE INTERSECTION
   ============================================================ */

static Hit trace_scene(Ray ray)
{
    Hit closest;

    closest.distance = 1e30;
    closest.hit = 0;

    for (int i = 0; i < NUM_SPHERES; i++)
    {
        if (spheres[i].type == SPHERE)
            intersect_sphere(ray, &spheres[i], &closest);

        else if (spheres[i].type == PLANE)
            intersect_plane(ray, &spheres[i], &closest);
    }

    return closest;
}

/* ============================================================
                     PROCEDURAL FLOOR
   ============================================================ */

static Vec3 floor_color(Vec3 p)
{
    int x = (int)floor(p.x);
    int z = (int)floor(p.z);

    if ((x + z) & 1)
        return v3(0.07, 0.08, 0.10);

    return v3(0.25, 0.27, 0.30);
}

/* ============================================================
                          SHADOW
   ============================================================ */

static int in_shadow(Vec3 point, Vec3 light_position)
{
    Vec3 to_light = sub(light_position, point);

    double distance_to_light = length3(to_light);

    Vec3 direction = normalize(to_light);

    Ray shadow_ray;

    shadow_ray.origin =
        add(point, mul(direction, 0.002));

    shadow_ray.direction = direction;

    Hit h = trace_scene(shadow_ray);

    return h.hit && h.distance < distance_to_light;
}

/* ============================================================
                      LIGHTING
   ============================================================ */

static Vec3 calculate_lighting(
    Vec3 point,
    Vec3 normal,
    Vec3 view,
    Material material
)
{
    Vec3 result =
        mul(material.color, material.ambient);

    for (int i = 0; i < NUM_LIGHTS; i++)
    {
        Light *light = &lights[i];

        Vec3 to_light =
            normalize(sub(light->position, point));

        double ndotl =
            dot(normal, to_light);

        if (ndotl <= 0)
            continue;

        if (in_shadow(point, light->position))
            continue;

        Vec3 diffuse =
            mul(
                hadamard(material.color, light->color),
                material.diffuse *
                ndotl *
                light->intensity
            );

        Vec3 reflected =
            reflect(
                mul(to_light, -1),
                normal
            );

        double spec =
            pow(
                fmax(0.0, dot(view, reflected)),
                material.shininess
            );

        Vec3 specular =
            mul(
                light->color,
                material.specular *
                spec *
                light->intensity
            );

        result = add(result, diffuse);
        result = add(result, specular);
    }

    return result;
}

/* ============================================================
                       SKY GRADIENT
   ============================================================ */

static Vec3 sky(Vec3 direction)
{
    double t = 0.5 * (direction.y + 1.0);

    Vec3 top =
        v3(0.02, 0.025, 0.07);

    Vec3 bottom =
        v3(0.35, 0.12, 0.05);

    return add(
        mul(bottom, 1.0-t),
        mul(top, t)
    );
}

/* ============================================================
                       RAY COLOR
   ============================================================ */

static Vec3 ray_color(
    Ray ray,
    int depth
)
{
    if (depth > MAX_DEPTH)
        return v3(0,0,0);

    Hit hit = trace_scene(ray);

    if (!hit.hit)
        return sky(ray.direction);

    Vec3 base_color = hit.material.color;

    /*
        Plane gets procedural checkerboard.
    */
    if (hit.normal.y > 0.9)
    {
        base_color =
            floor_color(hit.point);

        hit.material.color = base_color;
    }

    Vec3 view =
        normalize(mul(ray.direction, -1));

    Vec3 local =
        calculate_lighting(
            hit.point,
            hit.normal,
            view,
            hit.material
        );

    /*
        Reflection
    */
    if (hit.material.reflection > 0.001)
    {
        Vec3 reflected_direction =
            normalize(
                reflect(
                    ray.direction,
                    hit.normal
                )
            );

        Ray reflected_ray;

        reflected_ray.origin =
            add(
                hit.point,
                mul(reflected_direction, 0.003)
            );

        reflected_ray.direction =
            reflected_direction;

        Vec3 reflected =
            ray_color(
                reflected_ray,
                depth + 1
            );

        local =
            add(
                mul(
                    local,
                    1.0 - hit.material.reflection
                ),
                mul(
                    reflected,
                    hit.material.reflection
                )
            );
    }

    return local;
}

/* ============================================================
                         CAMERA RAY
   ============================================================ */

static Ray make_camera_ray(
    double u,
    double v
)
{
    double aspect =
        (double)WIDTH / HEIGHT;

    double scale =
        tan(camera.fov * 0.5 * PI / 180.0);

    double px =
        (2.0*u - 1.0) *
        aspect *
        scale;

    double py =
        (1.0 - 2.0*v) *
        scale;

    Vec3 direction =
        add(
            camera.forward,
            add(
                mul(camera.right, px),
                mul(camera.up, py)
            )
        );

    direction =
        normalize(direction);

    Ray ray;

    ray.origin = camera.position;
    ray.direction = direction;

    return ray;
}

/* ============================================================
                      COLOR PROCESSING
   ============================================================ */

static unsigned char to_byte(double x)
{
    /*
        Filmic-ish exposure curve.
    */

    x = 1.0 - exp(-x * 1.25);

    /*
        Gamma correction.
    */

    x = pow(
        fmax(0.0, fmin(1.0, x)),
        1.0 / 2.2
    );

    return (unsigned char)(x * 255.0 + 0.5);
}

/* ============================================================
                       IMAGE BUFFER
   ============================================================ */

static unsigned char *image;

/* ============================================================
                    MULTITHREADING
   ============================================================ */

typedef struct {
    int thread_id;
    int start_y;
    int end_y;
} ThreadData;

static void *render_thread(void *arg)
{
    ThreadData *data =
        (ThreadData *)arg;

    RNG rng;

    rng.state =
        0x123456789abcdefULL ^
        ((uint64_t)data->thread_id * 0x9e3779b97f4a7c15ULL);

    for (int y = data->start_y;
         y < data->end_y;
         y++)
    {
        for (int x = 0;
             x < WIDTH;
             x++)
        {
            Vec3 pixel =
                v3(0,0,0);

            for (int sample = 0;
                 sample < SAMPLES;
                 sample++)
            {
                /*
                    Stratified-ish random
                    subpixel sampling.
                */

                double jitter_x =
                    random01(&rng);

                double jitter_y =
                    random01(&rng);

                double u =
                    ((double)x +
                     jitter_x) /
                    WIDTH;

                double v =
                    ((double)y +
                     jitter_y) /
                    HEIGHT;

                Ray ray =
                    make_camera_ray(u,v);

                Vec3 color =
                    ray_color(ray,0);

                pixel =
                    add(pixel,color);
            }

            pixel =
                mul(pixel, 1.0 / SAMPLES);

            pixel =
                clamp3(pixel,0,1);

            int index =
                (y * WIDTH + x) * 3;

            image[index+0] =
                to_byte(pixel.x);

            image[index+1] =
                to_byte(pixel.y);

            image[index+2] =
                to_byte(pixel.z);
        }

        if (data->thread_id == 0 &&
            y % 20 == 0)
        {
            printf(
                "\rRendering: %5.1f%%",
                100.0 *
                (double)y /
                HEIGHT
            );

            fflush(stdout);
        }
    }

    return NULL;
}

/* ============================================================
                     MATERIAL HELPERS
   ============================================================ */

static Material material(
    Vec3 color,
    double reflection
)
{
    Material m;

    m.color = color;

    m.ambient = 0.05;
    m.diffuse = 0.85;
    m.specular = 0.5;

    m.shininess = 80.0;

    m.reflection = reflection;

    return m;
}

/* ============================================================
                       SCENE SETUP
   ============================================================ */

static void setup_scene(void)
{
    /*
        Ground plane
    */

    spheres[0].type =
        PLANE;

    spheres[0].position =
        v3(0,-2,0);

    spheres[0].normal =
        v3(0,1,0);

    spheres[0].material =
        material(
            v3(0.2,0.2,0.2),
            0.35
        );

    /*
        Main red sphere
    */

    spheres[1].type =
        SPHERE;

    spheres[1].position =
        v3(-3,0,0);

    spheres[1].radius =
        2.0;

    spheres[1].material =
        material(
            v3(0.65,0.035,0.025),
            0.55
        );

    /*
        Blue sphere
    */

    spheres[2].type =
        SPHERE;

    spheres[2].position =
        v3(2,0,-1);

    spheres[2].radius =
        2.0;

    spheres[2].material =
        material(
            v3(0.02,0.15,0.75),
            0.65
        );

    /*
        Gold sphere
    */

    spheres[3].type =
        SPHERE;

    spheres[3].position =
        v3(0,2.5,3);

    spheres[3].radius =
        1.2;

    spheres[3].material =
        material(
            v3(0.9,0.5,0.04),
            0.7
        );

    /*
        Small green sphere
    */

    spheres[4].type =
        SPHERE;

    spheres[4].position =
        v3(4,-0.8,3);

    spheres[4].radius =
        1.2;

    spheres[4].material =
        material(
            v3(0.04,0.6,0.12),
            0.4
        );

    /*
        Purple sphere
    */

    spheres[5].type =
        SPHERE;

    spheres[5].position =
        v3(-5,-0.8,4);

    spheres[5].radius =
        1.2;

    spheres[5].material =
        material(
            v3(0.45,0.03,0.65),
            0.75
        );

    /*
        Mirror sphere
    */

    spheres[6].type =
        SPHERE;

    spheres[6].position =
        v3(0,-0.4,-5);

    spheres[6].radius =
        1.6;

    spheres[6].material =
        material(
            v3(0.7,0.7,0.72),
            0.92
        );

    /*
        Lights
    */

    lights[0].position =
        v3(-6,8,2);

    lights[0].color =
        v3(1.0,0.35,0.25);

    lights[0].intensity =
        2.5;

    lights[1].position =
        v3(6,6,-3);

    lights[1].color =
        v3(0.25,0.4,1.0);

    lights[1].intensity =
        2.8;

    lights[2].position =
        v3(0,5,8);

    lights[2].color =
        v3(0.8,0.35,1.0);

    lights[2].intensity =
        2.0;

    /*
        Camera
    */

    camera.position =
        v3(0,2,14);

    Vec3 target =
        v3(0,0,0);

    camera.forward =
        normalize(
            sub(
                target,
                camera.position
            )
        );

    /*
        Construct orthogonal camera basis.
    */

    Vec3 world_up =
        v3(0,1,0);

    camera.right =
        normalize(
            cross(
                camera.forward,
                world_up
            )
        );

    camera.up =
        normalize(
            cross(
                camera.right,
                camera.forward
            )
        );

    camera.fov =
        55.0;
}

/* ============================================================
                           MAIN
   ============================================================ */

int main(void)
{
    printf(
        "\n"
        "========================================\n"
        "       ADVANCED C CPU RAY TRACER       \n"
        "========================================\n\n"
    );

    printf(
        "Resolution : %dx%d\n",
        WIDTH,
        HEIGHT
    );

    printf(
        "Samples    : %d / pixel\n",
        SAMPLES
    );

    printf(
        "Max depth  : %d\n",
        MAX_DEPTH
    );

    printf(
        "Threads    : %d\n\n",
        NUM_THREADS
    );

    setup_scene();

    image =
        malloc(
            (size_t)WIDTH *
            HEIGHT *
            3
        );

    if (!image)
    {
        fprintf(
            stderr,
            "Failed to allocate image memory.\n"
        );

        return 1;
    }

    pthread_t threads[NUM_THREADS];
    ThreadData data[NUM_THREADS];

    int rows_per_thread =
        HEIGHT / NUM_THREADS;

    for (int i = 0;
         i < NUM_THREADS;
         i++)
    {
        data[i].thread_id = i;

        data[i].start_y =
            i * rows_per_thread;

        data[i].end_y =
            (i == NUM_THREADS-1)
            ? HEIGHT
            : (i+1) * rows_per_thread;

        pthread_create(
            &threads[i],
            NULL,
            render_thread,
            &data[i]
        );
    }

    for (int i = 0;
         i < NUM_THREADS;
         i++)
    {
        pthread_join(
            threads[i],
            NULL
        );
    }

    printf(
        "\n\nSaving image...\n"
    );

    FILE *file =
        fopen(
            "render.ppm",
            "wb"
        );

    if (!file)
    {
        fprintf(
            stderr,
            "Could not create render.ppm\n"
        );

        free(image);

        return 1;
    }

    fprintf(
        file,
        "P6\n%d %d\n255\n",
        WIDTH,
        HEIGHT
    );

    fwrite(
        image,
        1,
        (size_t)WIDTH *
        HEIGHT *
        3,
        file
    );

    fclose(file);

    free(image);

    printf(
        "Done!\n"
        "Output: render.ppm\n\n"
    );

    return 0;
}