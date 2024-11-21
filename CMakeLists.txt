cmake_minimum_required(VERSION 3.29)
project(CI_GI_project_fin_semestre C)

set(CMAKE_C_STANDARD 11)

add_executable(CI_GI_project_fin_semestre
#        static/static_entie_to_lettre.c
#        me/reel_en_lettre.c
#        me/entie_en_lettre_st.c
#        static/static_reel.c
#        dinamic/dinamic_entiere.c)
        dinamic/dinamic_reel.c)
#        me/reel_en_lettre.c)




# Single copy command for the text file
configure_file(${CMAKE_SOURCE_DIR}/dinamic/french_numbers.txt
        ${CMAKE_BINARY_DIR}/french_numbers.txt COPYONLY)
