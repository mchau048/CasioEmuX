package com.example.casioemux

import android.os.Bundle
import android.opengl.GLSurfaceView
import androidx.appcompat.app.AppCompatActivity
import java.io.File
import java.io.FileOutputStream

class MainActivity : AppCompatActivity() {

    private lateinit var glSurfaceView: GLSurfaceView

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        // 1. Copy thư mục models từ assets ra bộ nhớ trong
        copyAssetsToInternalStorage()

        // 2. Lấy đường dẫn thư mục lưu trữ nội bộ và khởi tạo lõi giả lập
        val modelPath = File(filesDir, "models").absolutePath
        initEmulator(modelPath)

        // 3. Khởi tạo GLSurfaceView cho đồ họa OpenGL / ImGui
        glSurfaceView = GLSurfaceView(this).apply {
            setEGLContextClientVersion(2) // Sử dụng OpenGL ES 2.0
            setRenderer(EmulatorRenderer())
        }
        setContentView(glSurfaceView)
    }

    private fun copyAssetsToInternalStorage() {
        val assetManager = assets
        val files = assetManager.list("models") ?: return

        val destDir = File(filesDir, "models")
        if (!destDir.exists()) destDir.mkdirs()

        for (filename in files) {
            val outFile = File(destDir, filename)
            if (!outFile.exists()) {
                try {
                    assetManager.open("models/$filename").use { input ->
                        FileOutputStream(outFile).use { output ->
                            input.copyTo(output)
                        }
                    }
                } catch (e: Exception) {
                    e.printStackTrace()
                }
            }
        }
    }

    external fun initEmulator(modelPath: String)

    companion object {
        init {
            System.loadLibrary("casioemux")
        }
    }
}