##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=bmCoordinator
ConfigurationName      :=Debug
WorkspacePath          :=/Volumes/Datos/Daniel/GoogleDrive/DoctoradoDB/Articulo1/code/BM_FW/coordinator
ProjectPath            :=/Volumes/Datos/Daniel/GoogleDrive/DoctoradoDB/Articulo1/code/BM_FW/coordinator/bmCoordinator
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Daniel Vilas Perulan
Date                   :=06/05/2018
CodeLitePath           :="/Users/daniel/Library/Application Support/codelite"
LinkerName             :=/usr/bin/g++
SharedObjectLinkerName :=/usr/bin/g++ -dynamiclib -fPIC
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
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="bmCoordinator.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
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
AR       := /usr/bin/ar rcu
CXX      := /usr/bin/g++
CC       := /usr/bin/gcc
CXXFLAGS :=  -g -O0 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/as


##
## User defined environment variables
##
CodeLiteDir:=/private/var/folders/rz/54385wcn4y7gbgt44q29l8yc0000gn/T/AppTranslocation/9BF5E2D8-B9B7-4996-999D-04A07BB0096B/d/codelite.app/Contents/SharedSupport/
Objects0=$(IntermediateDirectory)/main.c$(ObjectSuffix) $(IntermediateDirectory)/datalogger.c$(ObjectSuffix) $(IntermediateDirectory)/proc_common.c$(ObjectSuffix) $(IntermediateDirectory)/remote_proc.c$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@test -d ./Debug || $(MakeDirCommand) ./Debug


$(IntermediateDirectory)/.d:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/main.c$(ObjectSuffix): main.c $(IntermediateDirectory)/main.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/Volumes/Datos/Daniel/GoogleDrive/DoctoradoDB/Articulo1/code/BM_FW/coordinator/bmCoordinator/main.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.c$(DependSuffix): main.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.c$(ObjectSuffix) -MF$(IntermediateDirectory)/main.c$(DependSuffix) -MM main.c

$(IntermediateDirectory)/main.c$(PreprocessSuffix): main.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.c$(PreprocessSuffix) main.c

$(IntermediateDirectory)/datalogger.c$(ObjectSuffix): datalogger.c $(IntermediateDirectory)/datalogger.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/Volumes/Datos/Daniel/GoogleDrive/DoctoradoDB/Articulo1/code/BM_FW/coordinator/bmCoordinator/datalogger.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/datalogger.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/datalogger.c$(DependSuffix): datalogger.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/datalogger.c$(ObjectSuffix) -MF$(IntermediateDirectory)/datalogger.c$(DependSuffix) -MM datalogger.c

$(IntermediateDirectory)/datalogger.c$(PreprocessSuffix): datalogger.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/datalogger.c$(PreprocessSuffix) datalogger.c

$(IntermediateDirectory)/proc_common.c$(ObjectSuffix): proc_common.c $(IntermediateDirectory)/proc_common.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/Volumes/Datos/Daniel/GoogleDrive/DoctoradoDB/Articulo1/code/BM_FW/coordinator/bmCoordinator/proc_common.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/proc_common.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/proc_common.c$(DependSuffix): proc_common.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/proc_common.c$(ObjectSuffix) -MF$(IntermediateDirectory)/proc_common.c$(DependSuffix) -MM proc_common.c

$(IntermediateDirectory)/proc_common.c$(PreprocessSuffix): proc_common.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/proc_common.c$(PreprocessSuffix) proc_common.c

$(IntermediateDirectory)/remote_proc.c$(ObjectSuffix): remote_proc.c $(IntermediateDirectory)/remote_proc.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/Volumes/Datos/Daniel/GoogleDrive/DoctoradoDB/Articulo1/code/BM_FW/coordinator/bmCoordinator/remote_proc.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/remote_proc.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/remote_proc.c$(DependSuffix): remote_proc.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/remote_proc.c$(ObjectSuffix) -MF$(IntermediateDirectory)/remote_proc.c$(DependSuffix) -MM remote_proc.c

$(IntermediateDirectory)/remote_proc.c$(PreprocessSuffix): remote_proc.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/remote_proc.c$(PreprocessSuffix) remote_proc.c


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


