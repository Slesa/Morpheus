#I @"Tools/Fake/tools"
#r "FakeLib.dll"

#I "tools/FSharp.Formatting/lib/net40"
#r "FSharp.Markdown.dll"

open Fake
open Fake.FileSystem
open Fake.AssemblyInfoFile


// properties
let projectName = "IniConfig"
let projectSummary = "A library to handle configuration files based on INI syntax."
let projectDescription = "Includes the library to deal with configuration files as well as a graphical editor and a command line interface."
let authors = ["J. Preiss"]
let mail = "joerg.preiss@slesa.de"
let homepage = "https://github.com/Slesa/Morpheus/tree/master/IniConfig"

let version =
  match buildServer with
  | TeamCity -> buildVersion
  | _ -> "0.1"


// directories 
let cwd = System.IO.Directory.GetCurrentDirectory() 
let binDir = cwd @@ "bin"
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
    CreateCSharpAssemblyInfo "./src/VersionInfo.cs"
        [Attribute.Company "Slesa Solutions"
         Attribute.Copyright "Copyright Slesa © 2013"
         Attribute.Trademark "Slesa Solutions"
         Attribute.Version version
         Attribute.FileVersion version]
)

let buildSolutions = 
  !! "src/IniConfig.Editor.sln"

let deploySolutions = 
  !! "setup/IniConfig.Setup.sln"

Target "Build" (fun _ ->
  MSBuildRelease buildDir "Build" buildSolutions
    |> Log "Build-Output: "
) 

Target "BuildTests" (fun _ ->
  MSBuildDebug testDir "Build" buildSolutions
    |> Log "SpecsBuild-Output: "
)
 
Target "Test" (fun _ ->
  !! (testDir @@ "*.Specs.dll") 
        |> MSpec (fun p -> 
                {p with
                    HtmlOutputDir = reportDir})
)

Target "Deploy" (fun _ ->
  let cwd = System.IO.Directory.GetCurrentDirectory() + buildDir
  Log "Current directory: " [ cwd ]

  let defines64 = "FileSource=" + buildDir + ";Version=" + version 
  Log "Current defines: " [ defines64 ]

  deploySolutions
    |> MSBuild deployDir "Build" (["ProductVersion", version; "Configuration","Release"; "Platform", "x86"; "DefineConstants", defines64])
      |> Log "Deploy-Output: "
)



Target "Default" DoNothing


// Dependencies
"Clean"
  =?> ("SetAssemblyInfo",not isLocalBuild ) 
  ==> "Build" <=> "BuildTests"
  ==> "Test"
  ==> "Deploy"
//"Deploy"
  ==> "Default"


RunParameterTargetOrDefault "target" "Default"

