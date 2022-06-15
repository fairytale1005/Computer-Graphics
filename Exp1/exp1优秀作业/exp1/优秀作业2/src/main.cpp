#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <numeric>
#include <iomanip>

#include "transform.h"
#include "shader.h"
#include "mesh.h"


namespace
{
    constexpr float pi = 3.14159265358979f;


    // 窗口和输入相关数据
    GLFWwindow* window;
    bool keydown[512];
    int win_w = 512;
    int win_h = 512;
    int win_start_x = 400;
    int win_start_y = 200;
    float cursor_dx;
    float cursor_dy;

    // 摄像机相关数据
    constexpr float camera_speed        = 5.0f;
    constexpr float camera_fast_speed   = 20.0f;
    constexpr float camera_slow_speed   = 1.0f;
    constexpr float camera_rot_speed    = 0.003f;
    vec3  camera_pos = vec3(2.0f, 0.0f, 13.0f);
    float camera_xrot;
    float camera_yrot;
    bool mouse_lock = true;

    // 渲染相关数据
    Shader shader;
    Mesh task1_mesh;
    Mesh task2_mesh;


    // 输出帮助信息
    void print_help()
    {
        std::cout << "Exp1 - 徐铭逸 22920202202931" << std::endl;
        std::cout << "操作: [ESC]退出 [W/A/S/D]移动 [Space/V]上下移动 [CTRL]加速 [L]释放/锁定鼠标" << std::endl;
    }

    // 窗口大小修改回调函数
    void framebuffer_size_callback(GLFWwindow* window, int width, int height)
    {
        win_w = width;
        win_h = height;
        glViewport(0, 0, width, height);
    }

    // 按键回调函数
    void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        if (action == GLFW_PRESS)
        {
            switch (key)
            {
            case GLFW_KEY_ESCAPE:
                glfwSetWindowShouldClose(window, true);
                break;
            case GLFW_KEY_L:
                mouse_lock = !mouse_lock;
                glfwSetInputMode(window, GLFW_CURSOR, mouse_lock ? GLFW_CURSOR_HIDDEN : GLFW_CURSOR_NORMAL);
                glfwSetCursorPos(window, win_w / 2, win_h / 2);
                cursor_dx = cursor_dy = 0.0;
                break;
            default:
                break;
            }
            keydown[key] = true;
        }
        if (action == GLFW_RELEASE)
            keydown[key] = false;
    }

    // 鼠标位置回调函数
    void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
    {
        if (mouse_lock)
        {
            cursor_dx += xpos - win_w / 2.0f;
            cursor_dy += ypos - win_h / 2.0f;
            glfwSetCursorPos(window, win_w / 2, win_h / 2);
        }
    }


    // 初始化GLAD和GLFW
    bool init_gl()
    {
        if (!glfwInit())
            return false;

        glfwWindowHint(GLFW_SAMPLES, 4);

        window = glfwCreateWindow(win_w, win_h, "", NULL, NULL);
        if (!window)
        {
            glfwTerminate();
            return false;
        }

        glfwMakeContextCurrent(window);
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
        glfwSetWindowPos(window, win_start_x, win_start_y);
        glfwFocusWindow(window);
        glfwSetCursorPos(window, win_w / 2, win_h / 2);
        // glfwSwapInterval(1);

        if (!gladLoadGL(glfwGetProcAddress))
            return false;

        return true;
    }

    // 初始化GLFW的回调函数
    void init_callback()
    {
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
        glfwSetKeyCallback(window, key_callback);
        glfwSetCursorPosCallback(window, cursor_position_callback);
    }

    // 初始化渲染状态
    bool init_render()
    {
        glViewport(0, 0, win_w, win_h);
        glEnable(GL_DEPTH_TEST);

        // 加载着色器
        if (!shader.load_from_file("res/shader/shader.vert", "res/shader/shader.frag"))
            return false;

        // 设置透视投影
        trans::projection::perspective(pi * 0.25f, (float)win_w / win_h, 0.1f, 1000.0f);
        trans::projection::apply(shader);

        return true;
    }


    // 根据参数加载一个xOy平面上的圆(环)的扇形所需的三角形到mesh (r1>r2)
    void load_fan(Mesh& mesh, const vec3& center, const vec3& color, float r1, float r2, float s, float t, float step)
    {
        // 如果区间横跨起点 拆成两部分
        if (s > t)
        {
            load_fan(mesh, center, color, r1, r2, s,    pi * 2.0f, step);
            load_fan(mesh, center, color, r1, r2, 0.0f, t,         step);
            return;
        }
        float theta1 = s, theta2;
        while (theta1 <= t)
        {
            theta1 += step, theta2 = std::min(t, theta1 + step);
            vec3 p1 = { cos(theta1), sin(theta1), 0.0 };
            vec3 p2 = { cos(theta2), sin(theta2), 0.0 };
            mesh.add(Triangle{
                    { p1 * r1 + center, color },
                    { p1 * r2 + center, color },
                    { p2 * r2 + center, color } });
            mesh.add(Triangle{
                    { p2 * r2 + center, color },
                    { p2 * r1 + center, color },
                    { p1 * r1 + center, color } });
        }
    }

    // 初始化Task1所需数据
    void init_task1()
    {
        load_fan(task1_mesh, vec3(0.0f), vec3(1.0f, 0.0f, 0.0f), 1.0f, 0.0f, pi * 0.00f, pi * 0.25f, 0.001f);
        load_fan(task1_mesh, vec3(0.0f), vec3(0.0f, 1.0f, 0.0f), 1.0f, 0.0f, pi * 0.25f, pi * 0.50f, 0.001f);
        load_fan(task1_mesh, vec3(0.0f), vec3(0.0f, 0.0f, 1.0f), 1.0f, 0.0f, pi * 0.50f, pi * 0.75f, 0.001f);
        load_fan(task1_mesh, vec3(0.0f), vec3(1.0f, 1.0f, 0.0f), 1.0f, 0.0f, pi * 0.75f, pi * 1.00f, 0.001f);
        load_fan(task1_mesh, vec3(0.0f), vec3(0.0f, 1.0f, 1.0f), 1.0f, 0.0f, pi * 1.00f, pi * 1.25f, 0.001f);
        load_fan(task1_mesh, vec3(0.0f), vec3(1.0f, 0.0f, 1.0f), 1.0f, 0.0f, pi * 1.25f, pi * 1.50f, 0.001f);
        load_fan(task1_mesh, vec3(0.0f), vec3(0.5f, 0.5f, 0.5f), 1.0f, 0.0f, pi * 1.50f, pi * 1.75f, 0.001f);
        load_fan(task1_mesh, vec3(0.0f), vec3(1.0f, 1.0f, 1.0f), 1.0f, 0.0f, pi * 1.75f, pi * 2.00f, 0.001f);
        task1_mesh.init();
    }
    
    // 初始化Task2所需数据
    void init_task2()
    {
        // blue
        load_fan(task2_mesh, vec3(-2.2f, 1.0f, 0.000f), vec3(0.0f, 107.0f, 176.0f)  / 255.0f, 1.0f, 0.8f, pi * 1.75f, pi * 0.75f, 0.001f);
        load_fan(task2_mesh, vec3(-2.2f, 1.0f, 0.002f), vec3(0.0f, 107.0f, 176.0f)  / 255.0f, 1.0f, 0.8f, pi * 0.75f, pi * 1.75f, 0.001f);
        // black
        load_fan(task2_mesh, vec3( 0.0f, 1.0f, 0.000f), vec3(29.0f, 24.0f, 21.0f)   / 255.0f, 1.0f, 0.8f, pi * 0.50f, pi * 1.25f, 0.001f);
        load_fan(task2_mesh, vec3( 0.0f, 1.0f, 0.004f), vec3(29.0f, 24.0f, 21.0f)   / 255.0f, 1.0f, 0.8f, pi * 1.75f, pi * 0.50f, 0.001f);
        load_fan(task2_mesh, vec3( 0.0f, 1.0f, 0.002f), vec3(29.0f, 24.0f, 21.0f)   / 255.0f, 1.0f, 0.8f, pi * 1.25f, pi * 1.75f, 0.001f);
        // red
        load_fan(task2_mesh, vec3( 2.2f, 1.0f, 0.002f), vec3(220.0f, 47.0f, 31.0f)  / 255.0f, 1.0f, 0.8f, pi * 0.25f, pi * 1.25f, 0.001f);
        load_fan(task2_mesh, vec3( 2.2f, 1.0f, 0.004f), vec3(220.0f, 47.0f, 31.0f)  / 255.0f, 1.0f, 0.8f, pi * 1.25f, pi * 0.25f, 0.001f);
        // green
        load_fan(task2_mesh, vec3( 1.1f, 0.0f, 0.003f), vec3(5.0f, 147.0f, 65.0f)   / 255.0f, 1.0f, 0.8f, pi * 0.00f, pi * 2.00f, 0.001f);
        // yellow
        load_fan(task2_mesh, vec3(-1.1f, 0.0f, 0.001f), vec3(239.0f, 169.0f, 13.0f) / 255.0f, 1.0f, 0.8f, pi * 0.00f, pi * 2.00f, 0.001f);

        task2_mesh.init();
    }


    // 逻辑更新（绘图以外的工作）
    void update(float elapsed)
    {
        // 玩家移动
        if (mouse_lock)
        {
            camera_xrot += cursor_dx * camera_rot_speed;
            camera_yrot -= cursor_dy * camera_rot_speed;
            while (camera_xrot > pi) camera_xrot -= pi * 2.0f;
            while (camera_xrot < -pi) camera_xrot += pi * 2.0f;
            camera_yrot = std::max(std::min(camera_yrot, pi * 0.49f), -pi * 0.49f);
            cursor_dx = 0.0f;
            cursor_dy = 0.0f;

            float s = sin(camera_xrot);
            float c = cos(camera_xrot);
            float delta = camera_speed;
            if (keydown[GLFW_KEY_LEFT_CONTROL]) delta = camera_fast_speed;
            if (keydown[GLFW_KEY_LEFT_SHIFT])   delta = camera_slow_speed;
            delta *= elapsed, s *= delta, c *= delta;
            if (keydown[GLFW_KEY_W]) camera_pos.z -= c, camera_pos.x += s;
            if (keydown[GLFW_KEY_S]) camera_pos.z += c, camera_pos.x -= s;
            if (keydown[GLFW_KEY_A]) camera_pos.z -= s, camera_pos.x -= c;
            if (keydown[GLFW_KEY_D]) camera_pos.z += s, camera_pos.x += c;
            if (keydown[GLFW_KEY_SPACE]) camera_pos.y += delta;
            if (keydown[GLFW_KEY_V])     camera_pos.y -= delta;
        }
    }

    // 绘制一帧
    void draw(float elapsed)
    {
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // 摄像机变换
        trans::view::identity();
        trans::view::rotate(camera_yrot, { -1.0f, 0.0f, 0.0f });
        trans::view::rotate(camera_xrot, { 0.0f, 1.0f, 0.0f });
        trans::view::translate(-camera_pos);
        trans::view::apply(shader);

        trans::model::identity();
        trans::model::translate({ sin(glfwGetTime()) * 5.0, 0.0f, -1.5f});
        trans::model::rotate(glfwGetTime(), { 0.0f, 0.0f, 1.0f });
        trans::model::apply(shader);
        task1_mesh.draw(shader);

        trans::model::identity();
        trans::model::translate({ 0.0f, 0.0f, -1.0f });
        trans::model::apply(shader);
        task2_mesh.draw(shader);
    }
}



int main(void)
{
    if (!init_gl())
        return system("pause") , -1;

    if (!init_render())
        return system("pause"), -1;
    
    init_callback();

    print_help();

    init_task1();
    init_task2();

    // 主循环
    while (!glfwWindowShouldClose(window))
    {
        // 记录时间，更新FPS
        static float elapsed = 0.0;
        static int fps;
        {  
            static constexpr float fps_update_interval = 0.5;
            static float last_time = 0.0;
            static float total_elapsed = 0;
            static int frame_count = 0;

            float current_time = glfwGetTime();
            elapsed = current_time - last_time;
            total_elapsed += elapsed;
            last_time = current_time;
            frame_count++;

            if (total_elapsed > fps_update_interval)
            {
                fps = frame_count / total_elapsed;
                total_elapsed = 0;
                frame_count = 0;
            }
        }

        // 设置标题
        {
            std::ostringstream title;
            title << std::setprecision(2) << std::fixed;
            title << "Exp1 - "
                << " Fps: " << fps
                << " Camera: (" << camera_pos.x << "," << camera_pos.y << "," << camera_pos.z << ")"
                << "(" << camera_xrot / pi * 180.0f << "," << camera_yrot / pi * 180.0f << ")";
            glfwSetWindowTitle(window, title.str().c_str());
        }
        

        update(elapsed);

        draw(elapsed);


        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}