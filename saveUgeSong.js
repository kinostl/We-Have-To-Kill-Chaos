export const saveUGESong = (song)=> {
  const buffer = new ArrayBuffer(1024 * 1024);
  const view = new DataView(buffer);
  let idx = 0;

  function addUint8(value) {
    view.setUint8(idx, value);
    idx += 1;
  }
  function addUint32(value) {
    view.setUint32(idx, value, true);
    idx += 4;
  }
  function addInt8(value) {
    view.setInt8(idx, value);
    idx += 1;
  }
  function addShortString(s) {
    view.setUint8(idx, s.length);
    idx += 1;
    const te = new TextEncoder();
    te.encodeInto(s, new Uint8Array(buffer, idx, idx + 255));
    idx += 255;
  }

  function addSubpattern(i) {
    addInt8(i.subpattern_enabled ? 1 : 0);
    for (let n = 0; n < 64; n++) {
      const subpattern = i.subpattern[n];
      addUint32(subpattern.note ?? 90);
      addUint32(0);
      addUint32(subpattern.jump ?? 0);
      addUint32(subpattern.effectcode ?? 0);
      addUint8(subpattern.effectparam ?? 0);
    }
  }
  function addDutyInstrument(type, i) {
    addUint32(type);

    addShortString(i.name || "");
    addUint32(i.length !== null ? 64 - i.length : 0);
    addUint8(i.length === null ? 0 : 1);
    addUint8(i.initial_volume);
    addUint32(i.volume_sweep_change < 0 ? 1 : 0);
    addUint8(
      i.volume_sweep_change !== 0 ? 8 - Math.abs(i.volume_sweep_change) : 0
    );

    addUint32(i.frequency_sweep_time);
    addUint32(i.frequency_sweep_shift < 0 ? 1 : 0);
    addUint32(Math.abs(i.frequency_sweep_shift));

    addUint8(i.duty_cycle);

    addUint32(0);
    addUint32(0);

    addUint32(0);

    addSubpattern(i);
  }

  function addWaveInstrument(type, i) {
    addUint32(type);

    addShortString(i.name || "");
    addUint32(i.length !== null ? 256 - i.length : 0);
    addUint8(i.length === null ? 0 : 1);
    addUint8(0);
    addUint32(0);
    addUint8(0);

    addUint32(0);
    addUint32(0);
    addUint32(0);

    addUint8(0);

    addUint32(i.volume);
    addUint32(i.wave_index);

    addUint32(0);

    addSubpattern(i);
  }

  function addNoiseInstrument(type, i) {
    addUint32(type);

    addShortString(i.name || "");
    addUint32(i.length !== null ? 64 - i.length : 0);
    addUint8(i.length === null ? 0 : 1);
    addUint8(i.initial_volume);
    addUint32(i.volume_sweep_change < 0 ? 1 : 0);
    addUint8(
      i.volume_sweep_change !== 0 ? 8 - Math.abs(i.volume_sweep_change) : 0
    );

    addUint32(0);
    addUint32(0);
    addUint32(0);

    addUint8(0);

    addUint32(0);
    addUint32(0);

    addUint32(i.bit_count === 7 ? 1 : 0);

    addSubpattern(i);
  }

  addUint32(6); // version
  addShortString(song.name);
  addShortString(song.artist);
  addShortString(song.comment);

  for (let n = 0; n < 15; n++) {
    addDutyInstrument(0, song.duty_instruments[n] || {});
  }
  for (let n = 0; n < 15; n++) {
    addWaveInstrument(1, song.wave_instruments[n] || {});
  }
  for (let n = 0; n < 15; n++) {
    addNoiseInstrument(2, song.noise_instruments[n] || {});
  }
  for (let n = 0; n < 16; n++) {
    for (let m = 0; m < 32; m++) {
      addUint8(song.waves[n] ? song.waves[n][m] : 0);
    }
  }
  addUint32(song.ticks_per_row);

  addInt8(song.timer_enabled ? 1 : 0);

  addUint32(song.timer_divider);

  addUint32(song.patterns.length * 4);
  let patternKey = 0;
  for (const pattern of song.patterns) {
    for (let track = 0; track < 4; track++) {
      addUint32(patternKey++);
      for (let m = 0; m < 64; m++) {
        const t = pattern[m][track];
        addUint32(t.note === null ? 90 : t.note);
        addUint32(t.instrument === null ? 0 : t.instrument + 1);
        addUint32(0);
        addUint32(t.effectcode === null ? 0 : t.effectcode);
        addUint8(t.effectparam === null ? 0 : t.effectparam);
      }
    }
  }
  for (let track = 0; track < 4; track++) {
    addUint32(song.sequence.length + 1); //amount of "orders" in a uge file has an off-by-one
    for (const i of song.sequence) {
      addUint32(i * 4 + track);
    }
    addUint32(0); // add the off-by-one error
  }
  for (let n = 0; n < 16; n++) {
    addUint32(0); //Add empty routines
  }

  return buffer.slice(0, idx);
};