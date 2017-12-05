#include <jni.h>
#include <android/log.h>
#include <android/bitmap.h>

#define  LOG_TAG    "libBitmapDemo"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

typedef struct 
{
	uint8_t alpha;
	uint8_t red;
	uint8_t green;
	uint8_t blue;
} argb;

/*
* convertToGray
* Pixel operation
*/
JNIEXPORT void JNICALL Java_com_example_bitmapdemo_MainActivity_convertBmp
	(JNIEnv * env, jobject  obj, jobject jsrcBitmap, jobject desBitmap){
    AndroidBitmapInfo srcInfo, dstInfo;
    if (ANDROID_BITMAP_RESULT_SUCCESS != AndroidBitmap_getInfo(env, jsrcBitmap, &srcInfo)
        || ANDROID_BITMAP_RESULT_SUCCESS != AndroidBitmap_getInfo(env, desBitmap, &dstInfo)) {
        LOGE("get bitmap info failed");
        return;
    }

    void *srcBuf, *dstBuf;
    if (ANDROID_BITMAP_RESULT_SUCCESS != AndroidBitmap_lockPixels(env, jsrcBitmap, &srcBuf)) {
        LOGE("lock src bitmap failed");
        return;
    }

    if (ANDROID_BITMAP_RESULT_SUCCESS != AndroidBitmap_lockPixels(env, desBitmap, &dstBuf)) {
        LOGE("lock dst bitmap failed");
        return;
    }

	LOGI("width=%d; height=%d; stride=%d; format=%d;flag=%d",
    		srcInfo.width, //  width=2700 (900*3)
    		srcInfo.height, // height=2025 (675*3)
    		srcInfo.stride, // stride=10800 (2700*4)
    		srcInfo.format, // format=1 (ANDROID_BITMAP_FORMAT_RGBA_8888=1)
    		srcInfo.flags); // flags=0 (ANDROID_BITMAP_RESULT_SUCCESS=0)

    int w = srcInfo.width;
    int h = srcInfo.height;
    int32_t *srcPixs = (int32_t *) srcBuf;
    int32_t *desPixs = (int32_t *) dstBuf;
    int alpha = 0xFF << 24;
	int i, j;
	int color;
	int red;
	int green;
	int blue;
    for (i = 0; i < h; i++) {
        for (j = 0; j < w; j++) {
            // get the color of per pixel 
            color = srcPixs[w * i + j];
            red = ((color & 0x00FF0000) >> 16);
            green = ((color & 0x0000FF00) >> 8);
            blue = color & 0x000000FF;
            color = (red + green + blue) / 3;
            color = alpha | (color << 16) | (color << 8) | color;
            desPixs[w * i + j] = color;
        }
    }
    AndroidBitmap_unlockPixels(env, jsrcBitmap);
    AndroidBitmap_unlockPixels(env, desBitmap);
}

