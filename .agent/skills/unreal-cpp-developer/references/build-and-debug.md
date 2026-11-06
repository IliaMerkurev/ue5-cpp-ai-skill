# Diagnose a build or plugin failure

## Establish what Unreal is building

1. Record the failing action, platform, target, configuration and first actionable diagnostic from the full log. Keep the file, module, symbol or asset named there. A final UBT or AutomationTool exit code is only a pointer back into that log.
2. Resolve the actual engine installation used by this build from its invocation or log. Check the project's `.uproject` and engine association, any project build scripts and the relevant `*.Target.cs` files. A custom engine association may be an ID. Use the resolved engine's version when checking headers or plugin compatibility.
3. For a plugin, locate its `.uplugin` in the project and engine plugin roots and check any additional search directories used by the project. Compare the plugin ID, its enabled state, declared module names/types and each affected module's `*.Build.cs`. If two copies exist, use build or startup logs to identify the selected path before editing. A binary-only plugin needs a compatible binary for the intended engine and platform. [Epic's plugin guide](https://dev.epicgames.com/documentation/en-us/unreal-engine/plugins-in-unreal-engine)

## Follow the first failing stage

| Stage | What to inspect |
| --- | --- |
| UBT rules or discovery | Check the named target, descriptor, module rules and eligibility for the platform and target type. Distinguish enabling a plugin dependency from declaring a C++ module dependency. |
| UnrealHeaderTool (UHT) | Start at the reflected declaration named by UHT. Check supported types and specifiers, header visibility and that the matching `.generated.h` is the last include. Edit the source declaration. |
| C++ compiler | Inspect the first failing translation unit, the exact installed API signature and the header that declares it. If an include seems to work only in a unity build, reproduce with unity disabled for the affected scope. |
| Linker | Trace the unresolved symbol to its definition and owning module. Check the function signature, export macro and dependency from the consuming module. |
| Cook, stage or package | Find which operation failed in the AutomationTool log. During cook, inspect the named asset, dependency and target-platform support. During staging or packaging, follow the named file, runtime dependency or platform-tool error. [Epic's packaging phases](https://dev.epicgames.com/documentation/en-us/unreal-engine/packaging-your-project) |

## Verify the consumer

Repeat the failing operation with the same inputs after a focused fix. Use the project's Editor target for Editor-only changes. When a runtime module's dependencies or exports change, also build the applicable Game, Client or Server target. Cook or package when the failure involves those phases. Record target, platform, configuration, outcome and any remaining untested step. [Epic's build configurations](https://dev.epicgames.com/documentation/en-us/unreal-engine/build-configurations-reference-for-unreal-engine)

For a reflected rename, identify serialized users and determine whether a compatible wrapper or Core Redirect is needed. Load a representative **existing** dependent Blueprint with a known override, compile it and confirm the value and behavior survive. For a Sequencer-bound property, evaluate two known frames and inspect the actual bound object. A redirect can remap a serialized field while a track still needs its binding checked. [Epic's Core Redirects guide](https://dev.epicgames.com/documentation/en-us/unreal-engine/core-redirects-in-unreal-engine)

**Example.** A plugin moved into the project builds for Editor but the Game target reports a dependency on `UnrealEd`. Confirm which copy was built, trace the dependency to its consuming module and move editor-only functionality behind the appropriate editor boundary. Rebuild Game, then verify the editor feature in the Editor target.
