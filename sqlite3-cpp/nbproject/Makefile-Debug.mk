#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/Column.o \
	${OBJECTDIR}/src/Database.o \
	${OBJECTDIR}/src/Exception.o \
	${OBJECTDIR}/src/Query.o \
	${OBJECTDIR}/src/Row.o \
	${OBJECTDIR}/src/Statement.o \
	${OBJECTDIR}/src/Transaction.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=`pkg-config --libs sqlite3`  

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libsqlite3-cpp.${CND_DLIB_EXT}

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libsqlite3-cpp.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libsqlite3-cpp.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} -shared -fPIC

${OBJECTDIR}/src/Column.o: src/Column.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -Iinclude `pkg-config --cflags sqlite3` -std=c++11  -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Column.o src/Column.cpp

${OBJECTDIR}/src/Database.o: src/Database.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -Iinclude `pkg-config --cflags sqlite3` -std=c++11  -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Database.o src/Database.cpp

${OBJECTDIR}/src/Exception.o: src/Exception.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -Iinclude `pkg-config --cflags sqlite3` -std=c++11  -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Exception.o src/Exception.cpp

${OBJECTDIR}/src/Query.o: src/Query.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -Iinclude `pkg-config --cflags sqlite3` -std=c++11  -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Query.o src/Query.cpp

${OBJECTDIR}/src/Row.o: src/Row.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -Iinclude `pkg-config --cflags sqlite3` -std=c++11  -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Row.o src/Row.cpp

${OBJECTDIR}/src/Statement.o: src/Statement.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -Iinclude `pkg-config --cflags sqlite3` -std=c++11  -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Statement.o src/Statement.cpp

${OBJECTDIR}/src/Transaction.o: src/Transaction.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -s -Iinclude `pkg-config --cflags sqlite3` -std=c++11  -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Transaction.o src/Transaction.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libsqlite3-cpp.${CND_DLIB_EXT}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
