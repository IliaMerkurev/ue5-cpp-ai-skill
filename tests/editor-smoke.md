# First session and live Editor check

Run this recipe on a machine with UE 5.8, an MCP-capable client and a disposable Blueprint project. It defines expected results. Record actual results for each run.

1. **Start a clean session.** Install the skill for the client under test, open the project root and start a fresh conversation. In your language, ask the assistant to establish how to work on this project. Omit the skill name, path and slash commands. Confirm that the client's skill trace or loaded instructions identify `unreal-cpp-developer`. If the client exposes only a catalog, record discovery and leave automatic activation unverified. Choose Editor access through MCP and restrict asset work to `/Game/SkillSmoke/`.
2. **Identify the Editor.** Open the disposable project with its MCP bridge enabled. Ask the agent to identify the project and current map with a read-only call. Compare against the open Editor before allowing asset edits. For the first unfamiliar Editor operation, if the server exposes `AgentSkillToolset`, list its skills and load a relevant one if present. Record what the server actually advertised.
3. **Author the fixture.** In the test folder create a map, an Actor Blueprint named `BP_SmokeLamp` and a Level Sequence named `LS_SmokeLamp`. Add a movable Point Light component named `ProbeLight` to the Blueprint, set its Intensity to 250, and compile it. Place one instance in the map with no property overrides or construction-script writes.
4. **Animate the component.** Bind the placed actor to the sequence and add an Intensity track for its `ProbeLight` component. Set the display rate to 24 fps and use a playback range of frames 0–23 inclusive. Use one active section with linear keys at display frame 0 (1000) and frame 20 (3000). Save only the fixture packages. Reopen the saved map and sequence from disk in a fresh Editor session. Reconnect to the correct instance.
5. **Read the evaluated result.** With Sequencer preview active, scrub to each display frame below, wait for evaluation, then read Intensity from the **bound component instance** in the Editor world. Record its object path, both numeric readbacks and the Blueprint compile result. Key values, class defaults and screenshots alone cannot establish this result.

| Display frame | Expected component Intensity | Tolerance |
| --- | ---: | ---: |
| 5 | 1500 | ±1 |
| 15 | 2500 | ±1 |

For each check record `passed`, `failed`, or `not verified`, together with the exact engine version, client version and bridge in use. Include the reason for any missing evidence. If the task also tests a gameplay interaction, run the agreed input in PIE, assert its expected outcome and stop PIE. Report a successful PIE launch separately.
