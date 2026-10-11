#include <jni.h>
#include <string>
#include <jni.h>
#include <string>
#include <android/log.h>
#include <GLES2/gl2.h>
#include <jni.h>
#include <string>
#include <android/log.h>
#include <GLES2/gl2.h>

// Thêm các include của Dear ImGui ở đây:
#include "imgui.h"
#include "backends/imgui_impl_android.h"
#include "backends/imgui_impl_opengl3.h"

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_casioemux_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}
#include <jni.h>
#include <string>
#include <android/log.h>

#define LOG_TAG "CasioEmuX_JNI"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

extern "C" JNIEXPORT void JNICALL
Java_com_example_casioemux_MainActivity_initEmulator(
        JNIEnv* env,
        jobject /* this */,
        jstring modelPathDir) {

    const char* path = env->GetStringUTFChars(modelPathDir, nullptr);
    if (path != nullptr) {
        LOGI("Model path received: %s", path);

        // Gọi hàm khởi tạo core của CasioEmuX tại đây (tùy thuộc vào header chính của project)
        // Ví dụ: Emulator::GetInstance().Initialize(path);

        env->ReleaseStringUTFChars(modelPathDir, path);
    }
}
extern "C" JNIEXPORT void JNICALL
Java_com_example_casioemux_EmulatorRenderer_nativeInitGL(
        JNIEnv* env,
        jobject /* this */) {
    LOGI("Initializing Dear ImGui...");

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui::StyleColorsDark();

    // Khởi tạo backend OpenGL ES 2.0 (hoặc 3.0 tuỳ cấu hình)
    ImGui_ImplOpenGL3_Init("#version 100");
}

extern "C" JNIEXPORT void JNICALL
Java_com_example_casioemux_EmulatorRenderer_nativeResize(
        JNIEnv* env,
        jobject /* this */,
        jint width,
        jint height) {
    LOGI("Surface resized: %d x %d", width, height);
    // Sau này sẽ cập nhật glViewport và kích thước ImGui ở đây
}

extern "C" JNIEXPORT void JNICALL
Java_com_example_casioemux_EmulatorRenderer_nativeRenderFrame(
        JNIEnv* env,
        jobject /* this */) {

    // 1. Bắt đầu khung hình mới cho ImGui
    ImGui_ImplOpenGL3_NewFrame();
    ImGui::NewFrame();

    // 2. Tạo một cửa sổ giao diện thử nghiệm
    ImGui::Begin("CasioEmuX Emulator");
    ImGui::Text("Chao mung den với CasioEmuX!");
    if (ImGui::Button("Nhan vao day")) {
        LOGI("Nut da duoc bam!");
    }
    ImGui::End();

    // 3. Render đồ họa ra màn hình OpenGL
    ImGui::Render();

    glClearColor(0.15f, 0.15f, 0.15f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}