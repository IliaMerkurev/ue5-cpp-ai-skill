# Unreal Engine 5 C++ AI Developer Skill

A reusable instruction package for AI coding assistants working on Unreal Engine 5 C++ games, components, and plugins. It combines Unreal-specific engineering guidance with project overrides, Blueprint-friendly APIs, and a strict **tooltip-only comment policy for generated code**.

The skill guides implementation and review; it does not guarantee compilation, runtime correctness, or performance. Engine version, project requirements, and actual validation remain authoritative.

## What it covers

- **Ownership and loading:** reflected strong references, weak observation, soft loading, and legitimate hard references; pointer types follow lifetime and loading needs.
- **Reflection and authoring:** Details, Blueprint, and Sequencer access; correct `Interp` placement; handling direct property writes without assuming setters run.
- **Lifecycle and callbacks:** timers, delegates, async proxies, cancellation, reentrant handlers, and stale-operation protection.
- **Tick and optimization:** capability versus activation, appropriate update frequency, cache invalidation, and source-supported improvements without unsupported performance claims.
- **Architecture:** runtime/editor separation, plugin independence, interfaces, Data Assets, Gameplay Tags, and Subsystems when the task calls for them.
- **Blueprint integration:** callable/pure functions, implementable/native events, World Context, public compatibility, and useful tooltips.
- **Everyday C++ work:** IWYU, Unreal naming and types, strings/localization, logging, input integration, runtime guards, and threading constraints.

## Comment policy

Final generated C++ contains only `/** ... */` comments used as Editor tooltips for `UPROPERTY` and `UFUNCTION` declarations. It contains no explanatory inline, function-body, or internal-variable comments. Clear names and structure express intent; longer explanations belong in external documentation.

**Template files intentionally retain instructional comments for the agent.** Those comments explain what to replace and where code belongs. They must not be carried into generated implementations. Existing genuine legal notices must be preserved; the templates do not invent an Epic Games copyright attribution.

The supplied formatter disables automatic namespace comments. Formatting alone does not enforce the full comment policy.

## Package layout

- [SKILL.md](.agent/skills/unreal-cpp-developer/SKILL.md): generic Unreal guidance and the comment policy.
- [custom_rules.md](.agent/skills/unreal-cpp-developer/custom_rules.md): project-specific overrides; no sample project requirements are enabled by default.
- [templates/](.agent/skills/unreal-cpp-developer/templates/): adaptable UObject header/source examples, with agent-facing instructions.
- [.clang-format](.clang-format): a starting formatting configuration; retain an existing project's conventions where applicable.

The repository keeps its existing `.agent/skills/unreal-cpp-developer` layout for compatibility. Maintain one installed copy of the skill, not separate competing copies for different editors.

## Installation and use

1. Download or clone this repository.
2. Copy the entire `unreal-cpp-developer` directory, including `custom_rules.md` and `templates`, into the skill location supported by your assistant. If your setup uses `.agent/skills`, preserve that layout; if it uses `.agents/skills`, copy the same directory there instead.
3. Configure your assistant to load `SKILL.md`, or explicitly reference it in your request. Folder naming alone does not guarantee automatic discovery in every editor.
4. Add your team's requirements to `custom_rules.md` or reference existing authoritative project documents. Keep product-specific rules separate from the shared skill.
5. Use the formatting file only if it fits the project and installed clang-format version. Do not overwrite existing formatting configuration blindly.

The skill identifier is `unreal-cpp-developer`. Existing setups that refer to the old space-separated identifier may need their reference updated; the repository folder path is unchanged.

For a new class, the assistant reads the templates, chooses the actual Actor/Component/Subsystem/UObject base, fills in the requested behavior, and removes instructional comments from the output. For existing code, it preserves public APIs and avoids unrelated rewrites.

## Updating an existing installation

This revision combines broader Unreal guidance with ownership, lifecycle, mutable-setting, and compatibility refinements. It corrects unconditional Tick disabling, blanket soft-reference recommendations, universal string-key replacement, and overly broad threading claims.

Replace the generic skill and templates together, but preserve your own `custom_rules.md` contents and review the new policy before applying it. Project-specific version numbering, component contracts, and validation restrictions are not bundled as generic Unreal requirements.

Validation must follow the user's authorization. A source review or skill-format check does not establish that generated C++ compiles or works in Unreal.

## Contributing

Keep guidance concise, technically grounded, and consistent with the templates and README. Explain when a recommendation applies rather than adding universal restrictions for isolated problems. Preserve the tooltip-only policy in generated code and the instructional comments in templates.

## License

[MIT License](LICENSE). Free to use, modify, and distribute under its terms.
