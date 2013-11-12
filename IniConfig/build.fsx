#I @"Tools/Fake/tools"
#r "FakeLib.dll"

#I "tools/FSharp.Formatting/lib/net40"
#r "FSharp.Markdown.dll"

open Fake
// open Fake.FileSystem
open Fake.AssemblyInfoFile


// properties
let projectName = "IniConfig"
let projectSummary = "A library to handle configuration files based on INI syntax."
let projectDescription = "Includes the library to deal with configuration files as well as a graphical editor and a command line interface."
let authors = ["J. Preiss"]
let mail = "joerg.preiss@slesa.de"
let homepage = "https://github.com/Slesa/Morpheus/tree/master/IniConfig"

let buildNumber =
    if hasBuildParam "version" then getBuildParam "version" else
    if isLocalBuild then "0" else
    buildVersion
let version = 
    "0.9." + buildNumber + ".0" 


// directories 
let binDir = "./bin"
let buildDir = binDir @@ "build"
let testDir = binDir @@ "test"
let deployDir = binDir @@ "deploy"
let nugetDir = binDir @@ "nuget"
let reportDir = binDir @@ "report"
let clickOnceDir = binDir @@ "clickonce"
let docsDir = binDir @@ "doc"


// Targets

Target "Clean" (fun _ ->
  CleanDirs [buildDir; testDir; deployDir; nugetDir; reportDir; clickOnceDir; docsDir ]
) 

Target "SetAssemblyInfo" (fun _ ->
    CreateCSharpAssemblyInfo "./src/IniConfig.Console/Properties/AssemblyInfo.cs"
        [Attribute.Title "IniConfig - Command line interface to edit files, application"
         Attribute.Guid "4639d91e-a60a-4eb1-8e36-425a69cf4934"
         Attribute.Product "IniConfig Configuration Files"
         Attribute.Company "Slesa Solutions"
         Attribute.Copyright "Copyright Slesa © 2013"
         Attribute.Trademark "Slesa Solutions"
         Attribute.Version version
         Attribute.FileVersion version]
    CreateCSharpAssemblyInfo "./src/IniConfig.Console.lib/Properties/AssemblyInfo.cs"
        [Attribute.Title "IniConfig - Command line interface to edit files, functionality"
         Attribute.Guid "0a2a3ffc-4faf-4997-8846-73981268991b"
         Attribute.Product "IniConfig Configuration Files"
         Attribute.Company "Slesa Solutions"
         Attribute.Copyright "Copyright Slesa © 2013"
         Attribute.Trademark "Slesa Solutions"
         Attribute.Version version
         Attribute.FileVersion version]
)

let solutions = 
  !! "src/IniConfig.Editor.sln"
    |> Scan
Target "Build" (fun _ ->
  MSBuildRelease buildDir "Build" solutions

    |> Log "Build-Output: "
) 

Target "BuildTests" (fun _ ->
  MSBuildDebug testDir "Build" solutions
    |> Log "SpecsBuild-Output: "
)
 
Target "Test" (fun _ ->
  !! (testDir @@ "*.specs.dll") 
        |> MSpec (fun p -> 
                {p with
                    ExcludeTags = ["HTTP"]
                    HtmlOutputDir = reportDir})
)
Target "Default" DoNothing


// Dependencies
"Clean"
  ==> "SetAssemblyInfo" 
//  =?> ("SetAssemblyInfo",not isLocalBuild ) 
  ==> "Build" <=> "BuildTests"
  ==> "Test"
  ==> "Default"


RunParameterTargetOrDefault "target" "Default"

