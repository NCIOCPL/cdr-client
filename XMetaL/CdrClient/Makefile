PROPERTIES=/p:Configuration=Release /p:Platform=Win32
rebuild:
	MSBuild.exe CdrClient.vcxproj /t:Rebuild $(PROPERTIES)

clean:
	rm -rf ipch *.sdf x64 *.vcxproj.user CdrClient *.suo
