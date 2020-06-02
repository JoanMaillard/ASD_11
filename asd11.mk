##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=asd11
ConfigurationName      :=Debug
WorkspaceConfiguration := $(ConfigurationName)
WorkspacePath          :=G:/cplusplus/cplusplus
ProjectPath            :=G:/cplusplus/L11/git
IntermediateDirectory  :=../../cplusplus/build-$(ConfigurationName)/__/L11/git
OutDir                 :=../../cplusplus/build-$(ConfigurationName)/__/L11/git
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Joan
Date                   :=02/06/2020
CodeLitePath           :="C:/Program Files/CodeLite"
LinkerName             :=G:/Mingw/bin/g++.exe
SharedObjectLinkerName :=G:/Mingw/bin/g++.exe -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=..\..\cplusplus\build-$(ConfigurationName)\bin\$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :=$(IntermediateDirectory)/ObjectsList.txt
PCHCompileFlags        :=
RcCmpOptions           := 
RcCompilerName         :=G:/Mingw/bin/windres.exe
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := G:/Mingw/bin/ar.exe rcu
CXX      := G:/Mingw/bin/g++.exe
CC       := G:/Mingw/bin/gcc.exe
CXXFLAGS :=  -g -O0 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := G:/Mingw/bin/as.exe


##
## User defined environment variables
##
CodeLiteDir:=C:\Program Files\CodeLite
Objects0=../../cplusplus/build-$(ConfigurationName)/__/L11/git/catch2_tests_bstTest.cpp$(ObjectSuffix) ../../cplusplus/build-$(ConfigurationName)/__/L11/git/catch2_tests_catch_main.cpp$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: MakeIntermediateDirs $(OutputFile)

$(OutputFile): ../../cplusplus/build-$(ConfigurationName)/__/L11/git/.d $(Objects) 
	@if not exist "..\..\cplusplus\build-$(ConfigurationName)\__\L11\git" mkdir "..\..\cplusplus\build-$(ConfigurationName)\__\L11\git"
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@if not exist "..\..\cplusplus\build-$(ConfigurationName)\__\L11\git" mkdir "..\..\cplusplus\build-$(ConfigurationName)\__\L11\git"
	@if not exist ""..\..\cplusplus\build-$(ConfigurationName)\bin"" mkdir ""..\..\cplusplus\build-$(ConfigurationName)\bin""

../../cplusplus/build-$(ConfigurationName)/__/L11/git/.d:
	@if not exist "..\..\cplusplus\build-$(ConfigurationName)\__\L11\git" mkdir "..\..\cplusplus\build-$(ConfigurationName)\__\L11\git"

PreBuild:


##
## Objects
##
../../cplusplus/build-$(ConfigurationName)/__/L11/git/catch2_tests_bstTest.cpp$(ObjectSuffix): catch2_tests/bstTest.cpp ../../cplusplus/build-$(ConfigurationName)/__/L11/git/catch2_tests_bstTest.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "G:/cplusplus/L11/git/catch2_tests/bstTest.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/catch2_tests_bstTest.cpp$(ObjectSuffix) $(IncludePath)
../../cplusplus/build-$(ConfigurationName)/__/L11/git/catch2_tests_bstTest.cpp$(DependSuffix): catch2_tests/bstTest.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../../cplusplus/build-$(ConfigurationName)/__/L11/git/catch2_tests_bstTest.cpp$(ObjectSuffix) -MF../../cplusplus/build-$(ConfigurationName)/__/L11/git/catch2_tests_bstTest.cpp$(DependSuffix) -MM catch2_tests/bstTest.cpp

../../cplusplus/build-$(ConfigurationName)/__/L11/git/catch2_tests_bstTest.cpp$(PreprocessSuffix): catch2_tests/bstTest.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../../cplusplus/build-$(ConfigurationName)/__/L11/git/catch2_tests_bstTest.cpp$(PreprocessSuffix) catch2_tests/bstTest.cpp

../../cplusplus/build-$(ConfigurationName)/__/L11/git/catch2_tests_catch_main.cpp$(ObjectSuffix): catch2_tests/catch_main.cpp ../../cplusplus/build-$(ConfigurationName)/__/L11/git/catch2_tests_catch_main.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "G:/cplusplus/L11/git/catch2_tests/catch_main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/catch2_tests_catch_main.cpp$(ObjectSuffix) $(IncludePath)
../../cplusplus/build-$(ConfigurationName)/__/L11/git/catch2_tests_catch_main.cpp$(DependSuffix): catch2_tests/catch_main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../../cplusplus/build-$(ConfigurationName)/__/L11/git/catch2_tests_catch_main.cpp$(ObjectSuffix) -MF../../cplusplus/build-$(ConfigurationName)/__/L11/git/catch2_tests_catch_main.cpp$(DependSuffix) -MM catch2_tests/catch_main.cpp

../../cplusplus/build-$(ConfigurationName)/__/L11/git/catch2_tests_catch_main.cpp$(PreprocessSuffix): catch2_tests/catch_main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../../cplusplus/build-$(ConfigurationName)/__/L11/git/catch2_tests_catch_main.cpp$(PreprocessSuffix) catch2_tests/catch_main.cpp


-include ../../cplusplus/build-$(ConfigurationName)/__/L11/git//*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r $(IntermediateDirectory)


