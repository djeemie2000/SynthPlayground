cmake_minimum_required (VERSION 2.6)
project (Mongoose)
ADD_DEFINITIONS(
	-std=c++11 # or -std=c++0x
	# other flags
)

add_library(Mongoose
    mongoose.c
    mongoose.h
)

