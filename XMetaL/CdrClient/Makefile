PROPERTIES=/p:Configuration=Release /p:Platform=win32
rebuild:
	MSBuild.exe CdrClient.vcxproj /t:Rebuild $(PROPERTIES)

clean:
	rm -rf ipch *.sdf Release *.vcxproj.user CdrClient *.suo
