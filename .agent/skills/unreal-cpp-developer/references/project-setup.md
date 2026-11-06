# Set up or revise a project's working rules

## Recognize the request

Use this workflow when the user wants to establish, import or revise how the agent works on an Unreal project. Infer that intent from the conversation in any language. No command, keyword, translation or exact example phrase is required. For example, “Давай настроимся на работу с этим проектом” and “¿Podemos dejar acordado cómo vamos a trabajar en este proyecto?” can both request first-time setup. A request to change one existing convention is a targeted update.

Keep the requested scope. Configuring a camera, fixing an MCP connection, creating a gameplay feature, or opening an unfamiliar project does not by itself request this workflow. If the user asks how setup *would* work or asks only for a review, inspect or explain as appropriate and leave files untouched.

## Discover before asking

1. Find the relevant `.uproject` or standalone `.uplugin` and the rules entry point for that scope. In a monorepo, resolve which project the user means before writing. A plugin's rules may apply only beneath its directory. If the project is unavailable, offer a draft or ask for its location. Only report settings as saved after a successful write to that project.
2. Inspect relevant repository instructions, the skill's `custom_rules.md`, any project-specific skills they reference, and existing PM, documentation and tracker conventions. Distinguish active requirements from template examples. Check the project descriptor, modules, engine association and available engine metadata for facts you need. Keep unresolved facts unknown.
3. Identify the user's existing choices from these sources and the conversation. Treat Editor/MCP preferences as durable policy. Actual connectivity, the open project and available tools are session observations. When access is available and within scope, verify them with a read-only query. A plugin descriptor or client configuration alone cannot establish live connectivity.
4. If earlier custom instructions exist only in a client's private settings, use text the user has supplied. Ask for the relevant excerpt only if needed. Keep personal settings and credentials out of shared project files.

## Resolve the remaining choices

Briefly state what you found, then group only the outstanding decisions into one short message in the user's language. Follow their language if they switch. Keep technical identifiers, paths and commands exact. Use the agreed documentation language, defaulting to the project's established written language or, for a new project, the user's language. Ask about language only when the choice is unclear and matters.

| Decision | What to settle if still open |
| --- | --- |
| Editor access | Work through Unreal Editor via MCP when available, or work from source files only? Discover enabled tools through the connection. Introduce a named extension only when its capabilities matter to a concrete need. |
| Project management | Use this skill's lightweight PM workflow, use a team-selected external skill, or turn automatic PM off? Reuse an existing explicit choice. If the team wants an external skill, identify which one. |
| Documentation | Which existing document owns requirements? Where should lasting decisions and verified implementation status go, and what changes warrant an update? A small prototype may need only project rules and a short README. |
| Task tracking | Does the team use Linear, GitHub Issues, a local list, or no tracker? If an external tracker is chosen, identify the relevant team/project and whether the agent may read, create, or update tasks. Keep one place responsible for task status. |

Choose PM independently of tracker, documentation and Editor access. For an external PM, inspect relevant installed or repository-provided skills and existing pointers. Offer a short list of real matches when helpful. A name, path or description from the user can identify the intended skill. If several match, ask which to use. A skill such as `project-development-manager` is an optional example. Its presence alone does not select it.

Record the chosen mode and, for an external skill, its exact identifier or a portable link to its file. Resolve Markdown links relative to the document containing them, including in nested plugin directories. Use that workflow for coordination. If it is unavailable, keep the selection, continue feasible engineering work, and surface the missing skill when coordination needs it. Record a fallback only if the team explicitly selects one. On existing projects, a missing PM field is a question for setup or a relevant coordination decision. It does not trigger onboarding during routine work.

Carry forward established engineering conventions such as Blueprint/Sequencer editability, plugin boundaries, validation and branch policy. Ask about additional constraints only when the answers affect this project. If an answer covers only part of the setup, apply the settled choices where useful and keep the others open. An explicit setup request covers writing the agreed project rules. Follow existing authorization separately for enabling/installing plugins, changing client settings, or writing to a tracker.

## Persist and reconcile

- Use the repository's authoritative project instructions. If there is no existing entry point, create `AGENTS.md` at the project root. If existing docs already own a convention, link to that document. A plugin's authoring contract belongs at plugin scope. Keep one authoritative copy of each rule.
- Preserve the supplied skill and legacy overrides during setup. A repository-owned `custom_rules.md` with active rules can remain authoritative and be linked. If its only copy is in a replaceable skill installation or private client settings, migrate the agreed, shareable rules into a project-owned location when the user wants them there. Carry over their original scope. Retire duplicates only as part of an agreed migration. Never import a blank template as project policy.
- For new Markdown content, use the two markers below around **only the section maintained by this workflow**. Keep them unchanged across languages. Write the contents in the agreed language. Add confirmed decisions, short relative links and any necessary scope. Create additional documents only when they have content the project needs.

  ```markdown
  <!-- unreal-cpp-developer:project-rules:start -->
  ## Project working rules
  - Use Editor MCP when available. Verify the active project before editing assets.
  - Use the built-in project-management workflow.
  - Maintain requirements in [PROJECT.md](PROJECT.md). Update them when accepted behavior changes.
  - Track work in Linear. Read access only.
  <!-- unreal-cpp-developer:project-rules:end -->
  ```

- On repeat setup, read the current contents, including manual edits inside the block. Apply only the requested or newly settled differences. Preserve unrelated text, scoped overrides and other tools' managed sections. Reuse the existing marker pair. For duplicate or malformed markers, resolve the affected boundary before writing. If the sources genuinely conflict, show the competing rules and ask which should govern the affected scope.
- When the agreed rules already match, leave the files untouched. Avoid setup timestamps, session availability snapshots, generated inventories and empty scaffolding. After a write, read back the affected section and review the diff. Report the changed rules and their location in the user's language. Mention an unverified connection only when it affects the result.
