# Work in a live Unreal Editor

Use this workflow when the task needs the running Editor and the project allows MCP. For a source-only task, work directly with C++, module descriptors or configuration. Keep the project's chosen workflow separate from the Editor's availability in the current session.

## Discover the connection

1. Reuse the project's configured bridge. Inspect the tools advertised to this client. A plugin descriptor on disk or a URL in a config file does not establish a live connection.
2. Identify the instance with a read-only request. Match its project path to the intended `.uproject` when available. Otherwise corroborate its identity using the configured instance and a project-specific asset or map. Resolve any ambiguity before writing, especially with multiple checkouts or Editors. Check whether the target is in the editor world or a Play In Editor (PIE) world.
3. Inspect the schema for the operation the task requires. In UE 5.8, native Unreal MCP defaults to tool search: use the advertised `list_toolsets`, `describe_toolset` and `call_tool` to discover and invoke the relevant operation. If the server exposes tools directly, use the returned schemas. Other bridges can use different names and arguments.
4. For an unfamiliar operation, check whether the connected Editor advertises `AgentSkillToolset`. Inspect its schema and invoke `ListSkills` to find workflows registered by the project, engine or plugins. Use `GetSkills` with the identifier or path returned for the relevant entry. Follow the matching workflow within the project's rules. If this toolset or a matching entry is absent, use the available operations directly. [Epic's project skill discovery workflow](https://github.com/EpicGames/unreal-engine-skills-for-claude-code-plugin/blob/main/skills/unreal-mcp/SKILL.md)

**When configuring a connection.** For UE 5.8, Epic ships the experimental Unreal MCP plugin (`ModelContextProtocol`). When the request includes connecting the Editor, enable the toolsets needed for the task and follow the guide for the actual engine version and client. Epic's client-config generator leaves an existing Codex TOML untouched. Merge the required setting with existing entries when applicable. Verify the connection with a read-only Editor query. The native endpoint is local by default. A remote repository session may have no route to the user's Editor. [Epic's Unreal MCP guide](https://dev.epicgames.com/documentation/unreal-engine/unreal-mcp-in-unreal-editor)

**Optional extensions.** In UE 5.8, an enabled VibeUE plugin registers additional tools on the same Unreal MCP connection. Discover and use the tools and task-specific guidance it advertises. Preserve any VibeUE-generated section in the client's instructions when updating project rules. Its UE 5.7 edition used a standalone server and has separate instructions. Suggest enabling a missing toolset or adding a compatible extension only when it supplies a capability the user needs. [VibeUE documentation and 5.7 archive](https://www.vibeue.com/docs)

## Edit and verify

1. Trace ownership to a concrete package and object. A value visible on an actor may come from a Blueprint class default, an instance override, a construction script or a Sequencer track. Inspect the current value, relevant runtime writers and unsaved edits before choosing the target.
2. Edit serialized assets such as `.uasset` and `.umap` through supported Editor APIs. Before a bulk edit, preview the affected packages and establish a recoverable checkpoint that preserves outstanding user edits. Use one writer and sequence calls to the same Editor. For Blueprint logic, compile the affected Blueprint and inspect the result. Wait for any compilation, import or shader work required by the check.
3. Save the affected packages deliberately. Preserve unrelated dirty packages and distinguish transient PIE changes from authored assets. Read back the saved change and reopen the asset when persistence is in question.
4. Check the requested behavior where it occurs. For a Sequencer edit, evaluate specific frames and read the resulting value on the bound object. For gameplay, exercise the interaction in PIE and observe the expected state change. An Editor or PIE startup check alone verifies startup. If a tool queues a scenario, wait for its terminal result. Report which package changed, which checks ran and any gap that matters to the user.

## Recover from an interruption

After a timeout or partial batch, re-read the affected objects before retrying. A create or graph edit may already have taken effect. After an Editor restart or reload, rediscover the instance, tools and objects. If the connection fails, inspect the configured endpoint and available Editor logs. Continue any feasible source work and identify the specific live check still outstanding.
