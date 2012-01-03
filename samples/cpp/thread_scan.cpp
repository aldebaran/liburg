/*!
  \file
  \brief Thread sample

  \author Satofumi KAMIMURA

  $Id: thread_scan.cpp 1854 2010-07-14 00:55:57Z satofumi $
*/

#include "UrgDevice.h"
#include "Thread.h"
#include "delay.h"
#include <iostream>
#include <cstdlib>

using namespace qrk;
using namespace std;

#define AUTO_CAPTURE_TEST


static int thread_function(void* args)
{
    UrgDevice urg;

    const char* device = static_cast<const char*>(args);
    if (! urg.connect(device)) {
        cout << "UrgDevice::connect: " << urg.what() << endl;
        exit(1);
    }
#if defined(AUTO_CAPTURE_TEST)
    urg.setCaptureMode(AutoCapture);
#endif

    enum { CaptureTimes = 10 };
    vector<long> data;
    int scan_times = 0;
    while (scan_times < CaptureTimes) {
        data.clear();
        long timestamp;
        if (urg.capture(data, &timestamp)) {
            cout << device << ": n = " << data.size()
                 << ", (" << timestamp << ')'
                 << ", " << scan_times << endl;
            ++scan_times;
        } else {
#if defined(AUTO_CAPTURE_TEST)
            delay(urg.scanMsec());
#endif
        }
        delay(1);
    }

    return 0;
}


int main(int argc, char *argv[])
{
    // Change the port name appropriately
#ifdef WINDOWS_OS
    const char *devices[] = {
        "COM3",
        "COM4",
    };
#else
    const char *devices[] = {
        "/dev/ttyACM0",
        "/dev/ttyACM1",
    };
#endif

    Thread *threads[2];
    for (int i = 0; i < 2; ++i) {
        threads[i] = new Thread(thread_function, const_cast<char *>(devices[i]));
        threads[i]->run();
    }

    for (int i = 0; i < 2; ++i) {
        threads[i]->wait();
    }

#ifdef MSC
    getchar();
#endif

    return 0;
}
