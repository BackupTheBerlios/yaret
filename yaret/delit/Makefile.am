####### kdevelop will overwrite this part!!! (begin)##########
bin_PROGRAMS = delit

## INCLUDES were found outside kdevelop specific part

delit_SOURCES = database.cpp clienttestdlg.cpp ClientDlg.cpp main.cpp 
SOURCES = database.cpp clienttestdlg.cpp ClientDlg.cpp main.cpp 
INTERFACES = 
TRANSLATIONS = 
KDE_OPTIONS = qtonly
delit_LDADD   =  $(LIB_QT) -lXext -lX11 $(LIBSOCKET)

SUBDIRS = docs 

EXTRA_DIST = main.cpp ClientDlg.cpp ClientDlg.h clienttestdlg.cpp clienttestdlg.h database.h database.cpp 

####### kdevelop will overwrite this part!!! (end)############


# set the include path for X, qt and KDE
INCLUDES= $(all_includes)

delit_METASOURCES = AUTO

# the library search path. 
delit_LDFLAGS = $(all_libraries) 

# them while "make clean", use CLEANFILES
DISTCLEANFILES = $(delit_METASOURCES)

# this is to enable Qt behavoir of am_edit




