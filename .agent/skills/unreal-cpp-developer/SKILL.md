---
name: unreal-cpp-developer
description: Develop or debug Unreal Engine 5 C++, plugins, build failures, Blueprints and Sequencer, including live Editor work through MCP. Use also when a user asks in any language to establish, import or revise an Unreal project's agent workflow, including project rules, optional project-management skills, documentation, task tracking and Editor access.
---

# Unreal Engine project development

## Project context and scope

Read the active instructions for the target repository and affected project/plugin. Follow their pointer to the project's custom conventions and respect any [legacy overrides](custom_rules.md) in their original scope. Apply explicit user instructions and scoped project conventions before the defaults here. Identify the relevant `.uproject` or `.uplugin` and the engine version. Check installed engine headers or version-matched documentation when API or lifecycle behavior is uncertain.

Infer the workflow from the user's intent. Use their language for conversation, setup questions and results. Keep project documents in the team's chosen writing language.

- **Establish or change the project's working agreements.** Follow [Project setup](references/project-setup.md), including for an existing project. Settle how to maintain the architecture overview and ask whether to define additional custom rules now or later. A later request to revise either choice updates just that part. Any natural phrasing can trigger these workflows. A request for advice or a preview calls for a read-only response. Configuring a gameplay feature, fixing a bug, or simply opening a new repository does not start onboarding.
- **Inspect or change something in Unreal Editor.** Follow [Editor and MCP](references/editor-mcp.md). Use the operations the connected project actually exposes. A Blueprint-only request can stay entirely in Blueprint.
- **Write, debug or review source.** Use the C++ guidance below for relevant code. Preserve the project's C++/Blueprint division, public names, serialized properties and asset references. Identify the migration path for an unavoidable compatibility change.
- **Diagnose a build or plugin failure.** Follow [Build and plugin diagnostics](references/build-and-debug.md) for target and module discovery, the first failing build stage, or verification of a reflected API change in its existing consumers.

## Choose the project's management workflow

Read the choice recorded for this project. An installed skill, a tracker link or the language of the conversation cannot establish that choice. Use one management workflow:

- **Built-in.** For a substantial feature, agree on the outcome, scope and acceptance check. Record decisions, dependencies and meaningful changes of status in the team's chosen documents or tracker. Keep proposals distinguishable from accepted requirements. For a small fix, a change description and its check usually suffice.
- **External skill.** Load the specific PM skill selected by the team when coordination is needed. It owns planning, milestone tracking and PM reports within the project's conventions. Keep Unreal implementation and verification here. If the selected skill is unavailable, report the gap when it affects the task and continue independent engineering work. Use a fallback only when the team has chosen one.
- **Off.** Run engineering tasks without initiating planning cycles, backlog maintenance or PM reports. Honor explicit requests and the team's standing documentation rules. A one-time request to prepare a plan or update an issue does not change the saved mode.

An existing project with no recorded choice can keep its current workflow. For an ordinary engineering task, proceed without introducing PM. Resolve the preference during setup or when a coordination request depends on it.

## Project documentation and verification

In any PM mode, follow the team's documentation language, sources and update policy. Typical homes are `AGENTS.md` for durable working rules, `PROJECT.md` for accepted requirements, and `docs/STATUS.md` for current implementation, evidence and known gaps.

**Architecture maintenance.** By default, keep one short overview of the implemented design. Read the relevant section before changing a system boundary. In the same change, update that section if ownership, module or plugin dependencies, public contracts, or important data flows change. For example, moving grab authority from a Pawn Blueprint into a replicated C++ component changes the overview. Tuning grab distance usually does not. Link to representative source or asset paths. Keep proposed designs clearly identified until implemented, and record the rationale for a lasting decision in an ADR if the project uses them. Respect an on-request, deferred or disabled policy recorded during setup.

Use the team's chosen tracker for active tasks when applicable (for example Linear, GitHub Issues or a local plan). Reference existing issues instead of keeping a second board. Selecting a tracker or PM skill alone grants no write access. If an agreed update requires unavailable access, identify that pending update.

Trace the behavior to the code, asset or instance that owns it and check the outcome in the relevant environment. State which checks actually ran, such as static review, compilation, Blueprint validation, PIE, packaging or a target-device check. Keep plans, reviews and implementation within the user's requested scope.

## Comments and templates

**Do not add explanatory comments to generated implementation code.** No inline logic comments, function-body comments, section banners, or comments on internal variables. Express intent through clear names, small functions, and explicit control flow. Explain algorithms, invariants, tradeoffs, and engine workarounds in external documentation or the change description.

The only comments to generate in final code are useful `/** ... */` tooltips for `UPROPERTY` and `UFUNCTION` declarations. Describe units, coordinate spaces, valid ranges, side effects, and parameters where relevant. Do not invent copyright notices; preserve genuine existing legal notices. Do not perform an unrelated repository-wide comment cleanup.

The [header](templates/TemplateClass.h) and [source](templates/TemplateClass.cpp) templates intentionally contain instructional comments for the agent. Keep those comments in the template files, but remove instructional placeholders when producing final code; retain only completed tooltips.

Read the templates when creating a new class. They demonstrate a minimal `UObject`, not a mandatory base for Actors, Components, Subsystems, or Slate types. Select the correct base and lifecycle, adapt the structure, and replace `TEMPLATE_CLASS_NAME`, `YOURMODULE_API`, categories, example members, and placeholder descriptions. Rename files and the generated-header include consistently.

## Reflection and authoring access

Choose property exposure from the authoring workflow rather than a blanket minimal-access rule:

- `EditAnywhere` and `EditDefaultsOnly` control Details editability; `BlueprintReadWrite` and `BlueprintReadOnly` control Blueprint access. Preserve broad editability where the project requires it.
- `Interp` is a **UPROPERTY specifier**, not metadata. Supported Sequencer tracks still depend on property type and engine integration.
- Keep caches, timers, physical indices, and other implementation state separate from user configuration. Expose deliberate queries where needed.
- Direct Blueprint or Sequencer property writes need not call setters or `PostEditChangeProperty`. Handle supported changes through appropriate invalidation, existing active updates, explicit refresh hooks, or inexpensive bounded synchronization. Do not make settings read-only to avoid this work.

```cpp
/** Angular speed in degrees per second. */
UPROPERTY(EditAnywhere, BlueprintReadWrite, Interp, Category = "Animation")
float AngularSpeed = 90.0f;
```

Use `BlueprintCallable` for commands and functions that need execution flow. Use `BlueprintPure` for side-effect-free queries, remembering they may be evaluated repeatedly. Mark C++ getters `const` where appropriate; constness alone does not make a query cheap.

Use `BlueprintImplementableEvent` when Blueprint supplies the implementation and `BlueprintNativeEvent` when C++ provides a default through `_Implementation`. Use delegates for subscriptions, with an explicit owner and cleanup. These are distinct mechanisms.

Static Blueprint functions that need a world should accept a suitable context object and use `meta = (WorldContext = "WorldContextObject")`. Handle missing contexts and multiple worlds; avoid global-world assumptions. Pure math helpers do not need a world context.

## Ownership and asset loading

| Need | Usual choice |
| --- | --- |
| Strong UObject member participating in GC | `UPROPERTY()` with `TObjectPtr<T>` in a reachable reflected owner |
| Observation without keeping a UObject alive | `TWeakObjectPtr<T>`, revalidated before use |
| Asset/class reference with deferred loading | `TSoftObjectPtr<T>` / `TSoftClassPtr<T>` |
| Required immediate class reference | `TSubclassOf<T>` |
| Non-owning local access or function parameter | Raw pointer or reference with a valid lifetime |

`TObjectPtr` alone in an unreflected structure is not a GC root. Choose explicit GC participation for non-UObject owners when necessary; do not assume a pointer wrapper makes an object reachable.

Hard references are appropriate for required assets and immediate use. Soft references are appropriate when deferred loading or avoiding a dependency chain matters; handle loading, failure, cancellation, and lifetime after loading. For substantial asynchronous asset loading, use the project's Asset Manager or streamable loading facilities.

Prefer configurable asset references over brittle hardcoded game-content paths. Do not automatically replace existing references or introduce asynchronous loading without a workflow need.

Use Unreal allocation/lifetime APIs for UObjects and actors rather than `new`/`delete`. Unreal shared pointers manage non-UObject data; they are not a substitute for UObject GC.

## Lifecycle, callbacks, and asynchronous work

Constructors establish defaults and default subobjects. World-dependent work belongs in appropriate lifecycle hooks. Registration can repeat in the editor: make setup idempotent and pair subscriptions/resources with cleanup. Use `OnRegister`, `InitializeComponent`, `PostInitializeComponents`, and `BeginPlay` according to the actual object's lifecycle.

Clear timers and detach subscriptions on cancellation, replacement, EndPlay, or destruction as applicable. Remove only bindings owned by the operation. Async action proxies should register only while they own an active operation and become ready for destruction when it ends.

Treat delegates, Blueprint events, actor spawning, and overlap callbacks as reentrant. Commit internal state before dispatch; revalidate object lifetime, operation identity, and relevant indices afterward. Do not retain container references across callbacks. Stable operation IDs or revisions can invalidate delayed work without confusing identity with a mutable array position.

A completion handler may start a replacement operation. Finish the old operation before calling the handler, and do not subsequently disable or clear the replacement.

Gameplay actor and component operations normally run on the game thread. Worker tasks may process isolated data or APIs explicitly documented as thread-safe. Do not describe every UObject operation or GC implementation as single-threaded. Returning to the game thread does not restore a destroyed object's lifetime: use appropriate weak references or explicit ownership, and reject stale results. Avoid unguarded raw `this` captures in delayed work.

## Tick and performance

`bCanEverTick` declares capability. Set it to false only when no Tick is needed. For objects that may tick later, enable capability and use `bStartWithTickEnabled = false` plus runtime activation (`SetComponentTickEnabled` or the Actor equivalent). Disable Tick when its work is inactive.

Continuous visual animation may need per-frame updates. Choose `TickInterval` from the required responsiveness; do not impose a generic 0.1-second interval. Prefer events for discrete changes. Timers also have overhead and cleanup costs; replacing Tick with many independent timers is not automatically an optimization.

Avoid repeated component searches, curve evaluation, allocations, and redundant transform updates when a localized change preserves behavior. Cache references or derived data only with a clear invalidation policy for runtime edits, replacement, and destruction.

Use `Reserve` when an expected collection size is useful. `TInlineComponentArray` can avoid heap allocations for counts that fit its inline capacity; it can still spill to the heap. Do not prohibit every cast or lookup in a loop without considering its cost and frequency.

Distinguish source-supported simplification from measured performance. Rendering changes can affect bounds, collision, and culling; fewer updates are not a success if visible behavior changes. Preserve coordinate-space and timing contracts, and defer changes requiring profiling or visual validation when that evidence is unavailable.

## Runtime safety and math

Use `IsValid` for UObject lifetime checks where appropriate. A validation check is not ownership and cannot make later asynchronous access safe.

`ensure` is non-fatal: its expression is evaluated in Shipping, while reporting depends on configuration. It does not replace control flow:

```cpp
if (!ensure(IsValid(Target)))
{
    return;
}
```

`check`/`checkf` generally stop execution on failure when enabled and are normally disabled in Shipping unless configured otherwise. Do not put required side effects in assertions. Use ordinary branches for recoverable input or runtime failures.

Editor clamp metadata does not validate arbitrary C++/Blueprint writes. Guard divisors, non-finite values, invalid durations, and capacity arithmetic. State Local/World spaces in APIs and tooltips; account for transformed parents and Unreal transform composition order.

## Architecture and modules

Keep reusable plugins independent of game-project modules. Separate runtime code from editor/compiler dependencies. Declare `Build.cs` dependencies as public when required by public headers and private otherwise; forward declarations do not eliminate actual module dependencies.

Use interfaces for shared behavior across unrelated types and delegates for notifications. When an interface supports Blueprint implementations, use the generated `Execute_` entry points rather than assuming a native interface pointer exists. Direct calls or casts are reasonable for intentional, concrete dependencies.

Use Data Assets for reusable definitions or shared configuration; retain per-instance properties for instance-specific settings. Use `UPrimaryDataAsset` when primary-asset management is needed. Use Gameplay Tags for extensible hierarchical categories, not as an automatic replacement for every enum or boolean.

Choose a GameInstance, World, or LocalPlayer Subsystem when a service genuinely needs that lifetime. Do not introduce global managers or a framework into autonomous components merely to follow a pattern.

For new player-input work, prefer Enhanced Input when supported by the target project. Preserve existing integrations unless migration is requested or required; do not add input dependencies to unrelated modules.

## Unreal types, style, and diagnostics

Prefer Unreal containers and strings in engine-facing code. Standard-library types remain appropriate at supported third-party or isolated boundaries. Respect module compiler settings; do not introduce C++ exceptions into modules built without them.

- `FText`: localized user-facing text.
- `FName`: identifier semantics, including its case-insensitive comparisons.
- `FString`: mutable text and string keys when their string/case semantics are required. Do not intern arbitrary unbounded input solely to replace a string key.

Use values for small scalar parameters and `const&` for appropriate larger read-only inputs, subject to reflection requirements. Use `auto` when it improves readability without hiding a meaningful type.

Follow Unreal prefixes (`U`, `A`, `F`, `E`, `I`, `T`, `S`, `b`) and existing project layout. Prefer scoped enums; choose underlying types to match reflection, flags, and API requirements rather than forcing every enum into `uint8`.

Follow IWYU, use forward declarations where sufficient, and keep `.generated.h` last among header includes. Use braces for all control flow. Expose user tuning through properties/assets and give internal constants meaningful names. Apply the project's formatting configuration without reformatting unrelated files.

Use dedicated log categories and actionable messages. Avoid unconditional per-frame log spam; use verbosity, gating, or rate limiting. Consider Visual Logger for spatial or time-dependent debugging when useful and authorized.

## Review and validation

Before delivery, review reflection declarations, ownership, callback cleanup, mutable settings, public compatibility, coordinate spaces, and module boundaries. Confirm the final code follows the tooltip-only comment policy; template guidance must not leak into generated code.

Validate according to the active task's authorization. Do not compile, run the editor, execute tests, install tooling, or benchmark against an explicit restriction. Report exactly what was checked and what remains deferred. Source review alone does not establish runtime correctness, saved-asset compatibility, or measured performance.
