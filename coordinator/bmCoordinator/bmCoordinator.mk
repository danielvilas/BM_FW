##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=bmCoordinator
ConfigurationName      :=Debug
WorkspacePath          :=/home/daniel/BM_FW/coordinator
ProjectPath            :=/home/daniel/BM_FW/coordinator/bmCoordinator
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=daniel
Date                   :=10/05/18
CodeLitePath           :=/home/daniel/.codelite
LinkerName             :=/usr/bin/g++
SharedObjectLinkerName :=/usr/bin/g++ -shared -fPIC
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
Libs                   := $(LibrarySwitch)yaml 
ArLibs                 :=  "yaml" 
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
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/main.c$(ObjectSuffix) $(IntermediateDirectory)/datalogger.c$(ObjectSuffix) $(IntermediateDirectory)/proc_common.c$(ObjectSuffix) $(IntermediateDirectory)/remote_proc.c$(ObjectSuffix) $(IntermediateDirectory)/config.c$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d "../.build-debug/rp_datalogger" $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

"../.build-debug/rp_datalogger":
	@$(MakeDirCommand) "../.build-debug"
	@echo stam > "../.build-debug/rp_datalogger"




MakeIntermediateDirs:
	@test -d ./Debug || $(MakeDirCommand) ./Debug


$(IntermediateDirectory)/.d:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/main.c$(ObjectSuffix): main.c $(IntermediateDirectory)/main.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/daniel/BM_FW/coordinator/bmCoordinator/main.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.c$(DependSuffix): main.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.c$(ObjectSuffix) -MF$(IntermediateDirectory)/main.c$(DependSuffix) -MM main.c

$(IntermediateDirectory)/main.c$(PreprocessSuffix): main.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.c$(PreprocessSuffix) main.c

$(IntermediateDirectory)/datalogger.c$(ObjectSuffix): datalogger.c $(IntermediateDirectory)/datalogger.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/daniel/BM_FW/coordinator/bmCoordinator/datalogger.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/datalogger.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/datalogger.c$(DependSuffix): datalogger.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/datalogger.c$(ObjectSuffix) -MF$(IntermediateDirectory)/datalogger.c$(DependSuffix) -MM datalogger.c

$(IntermediateDirectory)/datalogger.c$(PreprocessSuffix): datalogger.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/datalogger.c$(PreprocessSuffix) datalogger.c

$(IntermediateDirectory)/proc_common.c$(ObjectSuffix): proc_common.c $(IntermediateDirectory)/proc_common.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/daniel/BM_FW/coordinator/bmCoordinator/proc_common.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/proc_common.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/proc_common.c$(DependSuffix): proc_common.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/proc_common.c$(ObjectSuffix) -MF$(IntermediateDirectory)/proc_common.c$(DependSuffix) -MM proc_common.c

$(IntermediateDirectory)/proc_common.c$(PreprocessSuffix): proc_common.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/proc_common.c$(PreprocessSuffix) proc_common.c

$(IntermediateDirectory)/remote_proc.c$(ObjectSuffix): remote_proc.c $(IntermediateDirectory)/remote_proc.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/daniel/BM_FW/coordinator/bmCoordinator/remote_proc.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/remote_proc.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/remote_proc.c$(DependSuffix): remote_proc.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/remote_proc.c$(ObjectSuffix) -MF$(IntermediateDirectory)/remote_proc.c$(DependSuffix) -MM remote_proc.c

$(IntermediateDirectory)/remote_proc.c$(PreprocessSuffix): remote_proc.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/remote_proc.c$(PreprocessSuffix) remote_proc.c

$(IntermediateDirectory)/config.c$(ObjectSuffix): config.c $(IntermediateDirectory)/config.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/daniel/BM_FW/coordinator/bmCoordinator/config.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/config.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/config.c$(DependSuffix): config.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/config.c$(ObjectSuffix) -MF$(IntermediateDirectory)/config.c$(DependSuffix) -MM config.c

$(IntermediateDirectory)/config.c$(PreprocessSuffix): config.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/config.c$(PreprocessSuffix) config.c


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


