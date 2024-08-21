Use this to parse the string

```js
export const parseClipboardToPattern = (clipboard: string) => {
  const strToInt = (string: string, radix: number, offset = 0) => {
    const int = parseInt(string, radix);
    return isNaN(int) ? null : int + offset;
  };
  const rows = clipboard.split("\n");
  const pattern = rows
    .filter((r) => r[0] === "|")
    .map((r, i) => {
      console.log(`ROW ${i}: `, r);
      if (r[0] === "|") {
        const channel = r.substring(1).split("|");
        return channel.map((c, j) => {
          console.log(`CELL ${j}:`, c);
          const patternCell = new PatternCell();
          const cellString = [
            c.substring(0, 3),
            c.substring(3, 5),
            c.substring(8, 9),
            c.substring(9, 11),
          ];
          // Send NO_CHANGE_ON_PASTE to not change parameter when merging
          const note = noteStringsForClipboard.indexOf(cellString[0]);
          patternCell.note =
            cellString[0] !== "   "
              ? note === -1
                ? null
                : note
              : NO_CHANGE_ON_PASTE;
          patternCell.instrument =
            cellString[1] !== "  "
              ? strToInt(cellString[1], 10, -1)
              : NO_CHANGE_ON_PASTE;
          patternCell.effectcode =
            cellString[2] !== " "
              ? strToInt(cellString[2], 16)
              : NO_CHANGE_ON_PASTE;
          patternCell.effectparam =
            cellString[3] !== "  "
              ? strToInt(cellString[3], 16)
              : NO_CHANGE_ON_PASTE;
          return patternCell;
        });
      }
      throw new Error("Unsupported format");
    });

  return pattern;
};
```

Use this to open an UGE file

```js
    const song = await API.tracker.loadUGEFile(path);
```
    
Use this to make use of the pattern ?

```ts    
        editPattern: (
      state,
      _action: PayloadAction<{
        patternId: number;
        pattern: PatternCell[][];
      }>
    ) => {
      if (!state.song) {
        return;
      }
      const patternId = _action.payload.patternId;
      const patterns = cloneDeep(state.song.patterns);
      patterns[patternId] = _action.payload.pattern;
      state.song = {
        ...state.song,
        patterns,
      };
    }
```

Check https://github.com/chrismaltby/gb-studio/blob/develop/src/store/features/trackerDocument/trackerDocumentState.ts#L49 for more possibilities


```js
    addSequence: (state) => {
      if (!state.song) {
        return;
      }

      const newPatterns = [...state.song.patterns];
      const pattern = [];
      for (let n = 0; n < 64; n++)
        pattern.push([
          new PatternCell(),
          new PatternCell(),
          new PatternCell(),
          new PatternCell(),
        ]);
      newPatterns.push(pattern);

      const newSequence = [...state.song.sequence];
      newSequence.push(newPatterns.length - 1);

      state.song = {
        ...state.song,
        patterns: newPatterns,
        sequence: newSequence,
      };
    },
```

saveUGESong is what takes this kinda data and turns it into an actual UGE buffer

Song.ts defines what saveUGESong works with https://github.com/chrismaltby/gb-studio/blob/ff384734fb5ba8c768750b042ac8289e2b0285bb/src/shared/lib/uge/song/Song.ts



```js
  const buffer = saveUGESong(song);
  await writeFileWithBackupAsync(filename, new Uint8Array(buffer), "utf8");
```