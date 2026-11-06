# Unreal Engine 5 project skill

A reusable skill for AI assistants working on Unreal Engine 5 projects. It helps establish project rules, develop C++ and Blueprint features, and work in a running Unreal Editor through MCP when connected. The skill ID remains `unreal-cpp-developer`.

## Get started in your language

Install the skill in your assistant and open the Unreal project. Use your own words to ask it to set up your team's workflow. Here are three ways to ask.

- “Let's get you set up to work in this project.”
- «Давай договоримся, как ты будешь работать с этим проектом».
- 「このプロジェクトで今後どう作業するか、一緒に決めておこう。」

These are examples. The assistant recognizes the intent across languages and responds in the language you use. To explore the options first, just ask for an explanation. To revise one choice later, say what changed, for example “We've moved our tasks to Linear.”

On setup, the assistant reads existing project and plugin rules. It asks about unresolved choices such as Editor access, project management, where documentation belongs and which tracker the team uses. It records the answers in the project's existing instructions or a scoped `AGENTS.md`. Project documents can have a different language from the conversation. Future requests use these rules directly. Repeating setup preserves manual edits and applies new decisions.

### Choose how to manage work

| Project preference | What the assistant does |
| --- | --- |
| Built-in project management | Tracks scope, decisions, milestones and acceptance checks when a task needs coordination. |
| A team-selected PM skill | Uses the named skill for coordination. You can pick `project-development-manager` or give the name or path of your team's own skill. Unreal engineering stays with this skill. |
| Off | Works on the requested Unreal task and follows the project's documentation rules. Plans or tracker updates can still be requested individually. |

These choices are independent of the tracker. For example, a team can choose its own PM skill with a local task list, or turn PM off and still ask for a GitHub issue update. You can switch the PM choice later without redoing setup.

For live work, connect your assistant to the target Unreal Editor. The assistant discovers the operations available in that session, including tools added by enabled extensions. In UE 5.8, VibeUE adds tools to Unreal's native MCP connection. Source-only projects can use all project setup and C++ workflows. [Editor connection guide](.agent/skills/unreal-cpp-developer/references/editor-mcp.md)

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

- [SKILL.md](.agent/skills/unreal-cpp-developer/SKILL.md) contains workflow selection, documentation, delivery and Unreal C++ guidance.
- [Project setup](.agent/skills/unreal-cpp-developer/references/project-setup.md) covers first use, legacy project rules and subsequent revisions.
- [Editor and MCP](.agent/skills/unreal-cpp-developer/references/editor-mcp.md) covers capabilities, asset edits and verification.
- [Build and plugin diagnostics](.agent/skills/unreal-cpp-developer/references/build-and-debug.md) covers build targets, failure stages and checks for dependent assets.
- [custom_rules.md](.agent/skills/unreal-cpp-developer/custom_rules.md) remains available for installations with existing overrides.
- [templates/](.agent/skills/unreal-cpp-developer/templates/) contains adaptable UObject header and source examples.
- [.clang-format](.clang-format) provides a starting formatting configuration.

## Installation and use

Copy the entire [`unreal-cpp-developer` folder](.agent/skills/unreal-cpp-developer/) into **one** of the parent directories below. Project paths are relative to your Unreal repository. User paths apply to projects on that machine. Inside `unreal-cpp-developer/`, keep `SKILL.md` next to `references/` and `templates/`.

| Local client | One project | All projects for this user |
| --- | --- | --- |
| [Codex](https://learn.chatgpt.com/docs/build-skills) | `.agents/skills/` | `~/.agents/skills/` |
| [Claude Code](https://code.claude.com/docs/en/skills) | `.claude/skills/` | `~/.claude/skills/` |

For other clients, use their documented skill location. The source folder here retains its original `.agent/skills/` layout for clients configured to read it. The optional `.clang-format` is independent of skill installation.

Open a fresh session from the Unreal repository and check that the client's skill list includes `unreal-cpp-developer`. Then ask in your own language to set up how you will work together, without giving a skill name or path. The expected first step is to inspect project conventions and ask about unresolved choices. You can also start with a development task.

Codex CLI `0.167.0-alpha.4` discovered the skill in fresh sessions from both documented locations in an isolated test. That check queried the skill list. Selection for a natural-language request is a separate check. The Claude Code paths above follow Anthropic's documentation.

To move between computers, keep project-scoped skills and project-owned rules in version control, or install the user-scoped copy on each machine. For live Editor work, connect the local client to the correct Unreal instance on that machine and run the [Editor smoke test](tests/editor-smoke.md).

For a new class, the assistant reads the templates, chooses the actual Actor/Component/Subsystem/UObject base, fills in the requested behavior, and removes instructional comments from the output. For existing code, it preserves public APIs and avoids unrelated rewrites.

## Updating an existing installation

Keep your existing `custom_rules.md` and project/plugin-specific instructions when updating the installed package. Bring in the updated `SKILL.md`, templates and `references/` together. Ask the assistant to bring the project's working rules up to date. It can link to existing authoritative files or migrate agreed rules from a replaceable installation into the project. Keep the original until you have reviewed the migration.

Validation must follow the user's authorization. A source review or skill-format check does not establish that generated C++ compiles or works in Unreal.

## Contributing

Keep guidance concise, technically grounded, and consistent with the templates and README. Explain when a recommendation applies rather than adding universal restrictions for isolated problems. Preserve the tooltip-only policy in generated code and the instructional comments in templates.

## License

[MIT License](LICENSE). Free to use, modify, and distribute under its terms.
