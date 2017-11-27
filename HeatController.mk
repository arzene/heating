##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=HeatController
ConfigurationName      :=Debug
WorkspacePath          :="/home/sarge/projects/Raspberry Pi3/HeatController"
ProjectPath            :="/home/sarge/projects/Raspberry Pi3/HeatController"
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Stefano
Date                   :=22/10/17
CodeLitePath           :=/home/sarge/.codelite
LinkerName             :=/usr/bin/clang++
SharedObjectLinkerName :=/usr/bin/clang++ -shared -fPIC
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
ObjectsFileList        :="HeatController.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch)./include 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)event $(LibrarySwitch)jsoncpp 
ArLibs                 :=  "event" "jsoncpp" 
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := /usr/bin/ar rcu
CXX      := /usr/bin/clang++
CC       := /usr/bin/clang
CXXFLAGS :=  -g -O0 -std=c++11 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IntermediateDirectory)/source_I2CDevice.cpp$(ObjectSuffix) $(IntermediateDirectory)/HTU21DF.cpp$(ObjectSuffix) $(IntermediateDirectory)/source_httpserver.cpp$(ObjectSuffix) $(IntermediateDirectory)/source_HttpGetResponse.cpp$(ObjectSuffix) 



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
$(IntermediateDirectory)/main.cpp$(ObjectSuffix): main.cpp $(IntermediateDirectory)/main.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/sarge/projects/Raspberry Pi3/HeatController/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.cpp$(DependSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/main.cpp$(DependSuffix) -MM main.cpp

$(IntermediateDirectory)/main.cpp$(PreprocessSuffix): main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.cpp$(PreprocessSuffix) main.cpp

$(IntermediateDirectory)/source_I2CDevice.cpp$(ObjectSuffix): source/I2CDevice.cpp $(IntermediateDirectory)/source_I2CDevice.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/sarge/projects/Raspberry Pi3/HeatController/source/I2CDevice.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/source_I2CDevice.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/source_I2CDevice.cpp$(DependSuffix): source/I2CDevice.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/source_I2CDevice.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/source_I2CDevice.cpp$(DependSuffix) -MM source/I2CDevice.cpp

$(IntermediateDirectory)/source_I2CDevice.cpp$(PreprocessSuffix): source/I2CDevice.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/source_I2CDevice.cpp$(PreprocessSuffix) source/I2CDevice.cpp

$(IntermediateDirectory)/HTU21DF.cpp$(ObjectSuffix): HTU21DF.cpp $(IntermediateDirectory)/HTU21DF.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/sarge/projects/Raspberry Pi3/HeatController/HTU21DF.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/HTU21DF.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/HTU21DF.cpp$(DependSuffix): HTU21DF.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/HTU21DF.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/HTU21DF.cpp$(DependSuffix) -MM HTU21DF.cpp

$(IntermediateDirectory)/HTU21DF.cpp$(PreprocessSuffix): HTU21DF.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/HTU21DF.cpp$(PreprocessSuffix) HTU21DF.cpp

$(IntermediateDirectory)/source_httpserver.cpp$(ObjectSuffix): source/httpserver.cpp $(IntermediateDirectory)/source_httpserver.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/sarge/projects/Raspberry Pi3/HeatController/source/httpserver.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/source_httpserver.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/source_httpserver.cpp$(DependSuffix): source/httpserver.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/source_httpserver.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/source_httpserver.cpp$(DependSuffix) -MM source/httpserver.cpp

$(IntermediateDirectory)/source_httpserver.cpp$(PreprocessSuffix): source/httpserver.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/source_httpserver.cpp$(PreprocessSuffix) source/httpserver.cpp

$(IntermediateDirectory)/source_HttpGetResponse.cpp$(ObjectSuffix): source/HttpGetResponse.cpp $(IntermediateDirectory)/source_HttpGetResponse.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/sarge/projects/Raspberry Pi3/HeatController/source/HttpGetResponse.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/source_HttpGetResponse.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/source_HttpGetResponse.cpp$(DependSuffix): source/HttpGetResponse.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/source_HttpGetResponse.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/source_HttpGetResponse.cpp$(DependSuffix) -MM source/HttpGetResponse.cpp

$(IntermediateDirectory)/source_HttpGetResponse.cpp$(PreprocessSuffix): source/HttpGetResponse.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/source_HttpGetResponse.cpp$(PreprocessSuffix) source/HttpGetResponse.cpp


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


