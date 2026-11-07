cmake_minimum_required(VERSION 3.20)
project(Game LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(WIN32)
	# Point to the root directories (or the x86_64 subfolder if extracted from mingw archives)
	list(APPEND CMAKE_PREFIX_PATH
			"C:/libs/SDL3"
			"C:/libs/SDL3/x86_64-w64-mingw32"
			"C:/libs/SDL3_image"
			"C:/libs/SDL3_image/x86_64-w64-mingw32"
	)
endif()

find_package(SDL3 REQUIRED)
find_package(SDL3_image REQUIRED)

add_executable(Untitled-Game
		src/main.cpp
		src/Game.cpp
		src/Player.cpp
		include/Player.hpp
)

target_link_libraries(Untitled-Game PRIVATE
		SDL3::SDL3
		SDL3_image::SDL3_image
)

# Automatically copy both DLLs to the build folder
if(WIN32)
	add_custom_command(TARGET Untitled-Game POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy_if_different
			$<TARGET_FILE:SDL3::SDL3>
			$<TARGET_FILE_DIR:Untitled-Game>
			COMMENT "Copying SDL3.dll"
	)
	add_custom_command(TARGET Untitled-Game POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy_if_different
			$<TARGET_FILE:SDL3_image::SDL3_image>
			$<TARGET_FILE_DIR:Untitled-Game>
			COMMENT "Copying SDL3_image.dll"
	)
endif()