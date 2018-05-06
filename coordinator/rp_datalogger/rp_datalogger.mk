##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=rp_datalogger
ConfigurationName      :=Debug
WorkspacePath          :=/Volumes/Datos/Daniel/GoogleDrive/DoctoradoDB/Articulo1/code/BM_FW/coordinator
ProjectPath            :=/Volumes/Datos/Daniel/GoogleDrive/DoctoradoDB/Articulo1/code/BM_FW/coordinator/rp_datalogger
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Daniel Vilas Perulan
Date                   :=05/05/2018
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
ObjectsFileList        :="rp_datalogger.txt"
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
Objects0=$(IntermediateDirectory)/dataloger.c$(ObjectSuffix) 



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
$(IntermediateDirectory)/dataloger.c$(ObjectSuffix): dataloger.c $(IntermediateDirectory)/dataloger.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/Volumes/Datos/Daniel/GoogleDrive/DoctoradoDB/Articulo1/code/BM_FW/coordinator/rp_datalogger/dataloger.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/dataloger.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/dataloger.c$(DependSuffix): dataloger.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/dataloger.c$(ObjectSuffix) -MF$(IntermediateDirectory)/dataloger.c$(DependSuffix) -MM dataloger.c

$(IntermediateDirectory)/dataloger.c$(PreprocessSuffix): dataloger.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/dataloger.c$(PreprocessSuffix) dataloger.c


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


