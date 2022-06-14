#!/bin/bash

read -p "Enter build_system: " build_system

vendor/bin/premake/premake5 $build_system
#open VEngine.xcworkspace