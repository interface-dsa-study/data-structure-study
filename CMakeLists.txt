cmake_minimum_required(VERSION 3.25)

project(c-data-structure LANGUAGES C)

# ================================
# C 표준 설정
# ================================
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# ================================
# 기본 실행 파일 출력 경로
#
# 각 타깃의 상세 출력 경로는
# 아래 foreach 내부에서 다시 지정한다.
# ================================
set(
        CMAKE_RUNTIME_OUTPUT_DIRECTORY
        "${CMAKE_BINARY_DIR}/bin"
)

# ================================
# 공통 컴파일 경고 옵션
# ================================
add_library(dsa_project_options INTERFACE)

if (CMAKE_C_COMPILER_ID MATCHES "Clang|GNU")
    target_compile_options(
            dsa_project_options
            INTERFACE
            -Wall
            -Wextra
            -Wpedantic
    )
elseif (MSVC)
    target_compile_options(
            dsa_project_options
            INTERFACE
            /W4
    )
endif ()

# ================================
# Sanitizer 사용 여부
#
# AddressSanitizer:
# - 잘못된 메모리 접근
# - use-after-free
# - buffer overflow
#
# UndefinedBehaviorSanitizer:
# - 정의되지 않은 동작
# ================================
option(
        ENABLE_SANITIZER
        "Enable AddressSanitizer and UndefinedBehaviorSanitizer"
        ON
)

add_library(dsa_sanitizer_options INTERFACE)

# 수정된 부분:
# 일반적으로 Sanitizer는 Debug 빌드에서 사용하는 것이 적절하므로
# 생성기 표현식을 이용해 Debug 구성에만 적용한다.
if (
        ENABLE_SANITIZER
        AND CMAKE_C_COMPILER_ID MATCHES "Clang|GNU"
)
    target_compile_options(
            dsa_sanitizer_options
            INTERFACE
            "$<$<CONFIG:Debug>:-fsanitize=address,undefined>"
            "$<$<CONFIG:Debug>:-fno-omit-frame-pointer>"
    )

    target_link_options(
            dsa_sanitizer_options
            INTERFACE
            "$<$<CONFIG:Debug>:-fsanitize=address,undefined>"
    )
endif ()

# ================================
# 학습용 .c 파일 자동 탐색
#
# 현재 구조:
#
# data_structures/
# ├── 00_c_review/
# ├── 01_analyze/
# ├── 02_recursion/
# └── ...
#
# 추후 생성할 수 있는 구조:
#
# algorithms/
# problems/
#
# 중요:
# 각 .c 파일은 독립 실행 파일로 등록되므로
# 각 파일 안에 main() 함수가 있어야 한다.
# ================================
file(
        GLOB_RECURSE
        STUDY_SOURCE_FILES
        CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/data_structures/*.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/algorithms/*.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/problems/*.c"
)

# 수정된 부분:
# 운영체제나 파일 시스템에 관계없이
# 일정한 순서로 타깃이 등록되도록 정렬한다.
list(SORT STUDY_SOURCE_FILES)

# 수정된 부분:
# 탐색된 파일이 없을 때 상태를 명확하게 출력한다.
if (NOT STUDY_SOURCE_FILES)
    message(
            STATUS
            "No study source files were found."
    )
endif ()

# ================================
# 각 .c 파일을 독립 실행 타깃으로 등록
#
# 소스 파일:
#
# data_structures/00_c_review/p_01/chuseok22/solution.c
#
# CMake 타깃:
#
# data_structures_00_c_review_p_01_chuseok22_solution
#
# 실행 파일:
#
# cmake-build-debug/bin/
# └── data_structures/
#     └── 00_c_review/
#         └── p_01/
#             └── chuseok22/
#                 └── solution
# ================================
foreach (STUDY_SOURCE_FILE IN LISTS STUDY_SOURCE_FILES)

    # 프로젝트 루트를 기준으로 상대 경로를 구한다.
    file(
            RELATIVE_PATH
            STUDY_RELATIVE_PATH
            "${CMAKE_CURRENT_SOURCE_DIR}"
            "${STUDY_SOURCE_FILE}"
    )

    # 파일이 위치한 상대 디렉터리를 구한다.
    get_filename_component(
            STUDY_RELATIVE_DIRECTORY
            "${STUDY_RELATIVE_PATH}"
            DIRECTORY
    )

    # 확장자를 제외한 파일 이름을 구한다.
    get_filename_component(
            STUDY_FILE_NAME
            "${STUDY_SOURCE_FILE}"
            NAME_WE
    )

    # 디렉터리 경로와 파일 이름을 조합한다.
    set(
            STUDY_TARGET_RAW_NAME
            "${STUDY_RELATIVE_DIRECTORY}_${STUDY_FILE_NAME}"
    )

    # '/', '-', 공백 등을 안전한 식별자로 변환한다.
    string(
            MAKE_C_IDENTIFIER
            "${STUDY_TARGET_RAW_NAME}"
            STUDY_TARGET_NAME
    )

    # 수정된 부분:
    # 변환 결과가 기존 타깃 이름과 중복되면
    # 조용히 덮어쓰지 않고 명확한 오류를 발생시킨다.
    if (TARGET "${STUDY_TARGET_NAME}")
        message(
                FATAL_ERROR
                "Duplicate target name detected: ${STUDY_TARGET_NAME}\n"
                "Source file: ${STUDY_SOURCE_FILE}"
        )
    endif ()

    add_executable(
            "${STUDY_TARGET_NAME}"
            "${STUDY_SOURCE_FILE}"
    )

    set_target_properties(
            "${STUDY_TARGET_NAME}"
            PROPERTIES
            OUTPUT_NAME "${STUDY_FILE_NAME}"
            RUNTIME_OUTPUT_DIRECTORY
            "${CMAKE_BINARY_DIR}/bin/${STUDY_RELATIVE_DIRECTORY}"
    )

    target_link_libraries(
            "${STUDY_TARGET_NAME}"
            PRIVATE
            dsa_project_options
            dsa_sanitizer_options
    )

    # 수정된 부분:
    # CMake Reload 시 어떤 파일이 어떤 타깃으로
    # 등록되었는지 확인할 수 있도록 출력한다.
    message(
            STATUS
            "Registered target: ${STUDY_TARGET_NAME}"
            " <- ${STUDY_RELATIVE_PATH}"
    )

endforeach ()