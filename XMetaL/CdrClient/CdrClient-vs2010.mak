clean:
	rm -rf ipch *.sdf Release Debug *.vcxproj.user

rebuild:
	MSBuild CdrClient.vcxproj /t:Rebuild /p:Configuration=Release
