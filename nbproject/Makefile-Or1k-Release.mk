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
CC=or1k-linux-musl-gcc
CCC=or1k-linux-musl-g++
CXX=or1k-linux-musl-g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=Or1k
CND_DLIB_EXT=dll
CND_CONF=Or1k-Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/src/LithpAtom.o \
	${OBJECTDIR}/src/LithpDict.o \
	${OBJECTDIR}/src/LithpExceptions.o \
	${OBJECTDIR}/src/LithpInteger.o \
	${OBJECTDIR}/src/LithpList.o \
	${OBJECTDIR}/src/LithpPrimitive.o \
	${OBJECTDIR}/src/LithpString.o


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
LDLIBSOPTIONS=-s -static

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/lithp

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/lithp: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/lithp ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Iinclude -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/src/LithpAtom.o: src/LithpAtom.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Iinclude -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/LithpAtom.o src/LithpAtom.cpp

${OBJECTDIR}/src/LithpDict.o: src/LithpDict.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Iinclude -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/LithpDict.o src/LithpDict.cpp

${OBJECTDIR}/src/LithpExceptions.o: src/LithpExceptions.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Iinclude -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/LithpExceptions.o src/LithpExceptions.cpp

${OBJECTDIR}/src/LithpInteger.o: src/LithpInteger.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Iinclude -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/LithpInteger.o src/LithpInteger.cpp

${OBJECTDIR}/src/LithpList.o: src/LithpList.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Iinclude -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/LithpList.o src/LithpList.cpp

${OBJECTDIR}/src/LithpPrimitive.o: src/LithpPrimitive.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Iinclude -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/LithpPrimitive.o src/LithpPrimitive.cpp

${OBJECTDIR}/src/LithpString.o: src/LithpString.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -Iinclude -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/LithpString.o src/LithpString.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/lithp.exe

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
