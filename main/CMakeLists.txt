# Edit following two lines to set component requirements (see docs)
set(COMPONENT_REQUIRES )
set(COMPONENT_PRIV_REQUIRES )

set(COMPONENT_SRCS  "demoApp.c" 
                    "process.c" 
                    "main.c"
                    "system.c"
                    "demoApp2.c")
set(COMPONENT_ADD_INCLUDEDIRS "")

register_component()
