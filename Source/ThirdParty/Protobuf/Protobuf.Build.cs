// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;

public class Protobuf : ModuleRules
{
	public Protobuf(ReadOnlyTargetRules Target) : base(Target)
	{

		//Type = ModuleType.External;
		Type = ModuleType.External;
		//PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		//string modulePath = Path.GetFullPath(ModuleDirectory);
		//PublicDefinitions.Add("GOOGLE_PROTOBUF_NO_RTTI=1");
		PublicIncludePaths.AddRange(
			new string[] {
				Path.Combine(ModuleDirectory, "public")
				// ... add public include paths required here ...
			}
			);
		if (Target.Platform == UnrealTargetPlatform.Win64)
        {

			PublicIncludePaths.AddRange(
				new string[] {
							Path.Combine(ModuleDirectory, "Win64", "include")
					// ... add public include paths required here ...
				}
			);
			PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "Win64", "lib", "libprotobuf.lib"));
		}
        else if(Target.Platform == UnrealTargetPlatform.Mac)
        {

        }
			//PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "lib", "libprotobufd.lib"));
			//PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "lib", "libprotobuf.lib"));
		//PublicAdditionalLibraries.Add(Path.Combine(DllPath, "lib", "libprotobuf-lite.lib"));
		//PublicAdditionalLibraries.Add(Path.Combine(DllPath, "lib", "libprotoc.lib"));

		//PublicDelayLoadDLLs.Add("libprotobuf-lite.dll");
		//PublicDelayLoadDLLs.Add("libprotobuf-lite.dll");

		//RuntimeDependencies.Add(Path.Combine(DllPath, "bin", "libprotobuf.dll"));
		//RuntimeDependencies.Add(Path.Combine(DllPath, "bin", "libprotobuf-lite.dll"));
		//RuntimeDependencies.Add(Path.Combine(RuntimePath, "bin", "libprotoc.dll"));
		PrivateIncludePaths.AddRange(
			new string[] {
				//Path.Combine(ModuleDirectory, "public")
				// ... add other private include paths required here ...
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);
	}
}
