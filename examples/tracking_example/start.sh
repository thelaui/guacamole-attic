#!/bin/bash
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:.:../../lib:../../../../lib/linux_x86:/usr/lib/nvidia-current/:/opt/cuda/current/lib64:/opt/boost/current/lib:/opt/cuda/current/cuda/lib64 bin/tracking_example
