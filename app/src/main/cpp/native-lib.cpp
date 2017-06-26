#include <jni.h>
#include <string>
#include "android/log.h"
#include <sys/mman.h>

uint32_t code[] = {
        0xE3A0106F,
        0xE3A0206F,
        0xE3A0306F,
        0xE3A0406F,
        0xE3A0506F,
        0xE3A0606F,
        0xE3A0706F,
        0xE3A0806F
};


void text_segment(void){
    int a = 0;
    a++;
    printf("%d", a);
}


extern "C"
JNIEXPORT jboolean JNICALL
Java_com_example_dssiam_fortests_MainActivity_TextExec(
        JNIEnv *env,
        jobject /* this */) {

    (unsigned long (*)()) code;

    void *txt_sgm = (void *)text_segment;
    unsigned long adr = (unsigned long) txt_sgm;

    adr -= adr % PAGE_SIZE;

    txt_sgm = (void *) adr;

    if (-1 == mprotect(txt_sgm , sizeof(code), PROT_EXEC | PROT_READ | PROT_WRITE)) {
        __android_log_print(5, "WARN", "%s", "fail");
        return (jboolean) false;

    } else {
        memcpy(txt_sgm, code, sizeof(code));

        text_segment();

        __android_log_print(5, "WARN", "%s", "END");

        return (jboolean) true;
    }




}
