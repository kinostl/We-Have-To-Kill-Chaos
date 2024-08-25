import {
  exportToC,
  loadUGESong,
  saveUGESong,
} from "shared/lib/uge/ugeHelper";
import { noteStringsForClipboard } from "shared/lib/music/constants";
import { readFileSync, writeFileSync } from "fs-extra";

const data = readFileSync(`./song_template_v6.uge`);
const nsf = readFileSync(`./ff1_prolog_raw_famistudio.txt`, 'utf-8');

const dataArray = new Uint8Array(data).buffer;
const song = loadUGESong(dataArray);

// Okay so my plan is to load the template, convert the famitracker stuff to the patterns that the Patterns array expects, and then just see if saving that works as expected.

// patterns contains an array of arrays. those arrays represent the 4 slots in the song - Duty 1, Duty 2, Wave, Noise
const instrumentMap = {
  "Duty 0": 6,
  "Duty 1": 7
}

// Need to seperate into channels, then patterns, then subpatterns
// A channel is what maps to Duty 1 / 2 / Wave / Noise
// Instrument is Instrument
// Value is Note
// Other stuff not relevant yet


function convertToCellsObject(row){
  const cells = row.split("\" ")      
  const props = cells.map((cell)=>cell.trim().split("="))
  return props.reduce((prop_obj, x) => {
    prop_obj[x[0]] = x[1].replaceAll("\"","")
    return prop_obj
  }, {})
}

const nullCell = () => ({
  instrument: null,
  note: null,
  effectcode: null,
  effectparam: null
})

function getOffset(channel){
  return channel.reduce((offset, cell)=>{
    if(!cell || !cell.Value) return offset
    if(cell.Value.length == 2){
      cell.Value = `${cell.Value[0]}-${cell.Value[1]}`
    }
    
    const noteVal = noteStringsForClipboard.indexOf(cell.Value)
    let octave = 3
    if(noteVal < 0){
      octave = cell.Value[2]
      
      if(octave > 8){
        throw `Octave offset only goes up: ${cell.Value}`
      }
    }
    
    return Math.max(offset, 3 - octave)
  }, 0)
}

function convertToCell(cell, octave_offset){
  if(!cell || !cell.Value) return nullCell()
    if(cell.Value.length == 2){
      cell.Value = `${cell.Value[0]}-${cell.Value[1]}`
    }
    
    cell.Value = `${cell.Value[0]}${cell.Value[1]}${parseInt(cell.Value[2]) + octave_offset}`
    
  const noteVal = noteStringsForClipboard.indexOf(cell.Value)
  const out = {
    instrument: instrumentMap[cell.Instrument] || null,
    note: noteVal,
    effectcode: null,
    effectparam: null
  }
  
  if(out.note < 0) out.note = null
  if(cell["FinePitch"] == 0){
    out.effectcode=1
    out.effectparam=2
  }
  if(cell["FinePitch"] == 1){
    out.effectcode=2
    out.effectparam=2
  }
  
  return out
}

function prepareChannel(channel){
  let pattern_index=0;
  let previous_note=0;
  
  return channel.map(convertToCellsObject).map((x) => {
    const note_value = Math.ceil(parseInt(x["Note Time"]) / 4)
    if(note_value < previous_note){
      pattern_index++
    }
    x.note_index = note_value + (pattern_index * 64)
    x.duration = Math.ceil(parseInt(x["Duration"]) / 4)
    previous_note = note_value
    return x
  })
}

function padChannel(channel, octave_offset){
  let prev_duration = -1
  const output =  channel.reduce((arr, x)=>{
      if(!x.Value || !x.Instrument){
        return arr
      }
      const cell = convertToCell(x, octave_offset)
      let null_index=0
      
      while(arr.length < x.note_index){
        const buffCell = nullCell()
        if(null_index == prev_duration){
          buffCell.instrument = 14
          buffCell.note = cell.note
        }
        arr.push(buffCell)
        null_index++
      }

      arr.push(cell)

      if(x.duration > 0){
        prev_duration = x.duration
      }
      return arr
    },[])
  
  return output
}

function convertNsfToUgePattern(nsf_file){
    let current_channel = -1
    const channels = []
    let note_number=0
    let current_pattern=0
    nsf_file.split('\n').map((x)=>x.trim()).forEach((row)=>{
      if (row.startsWith("Channel")) {
        current_channel++;
        current_pattern=0
        channels[current_channel] = []
      }
      if (row.startsWith("Note")) {
        channels[current_channel].push(row.trim())
      }
    })
    
    let n_i=0;
    
    const c_0=prepareChannel(channels[0])
    const c_1=prepareChannel(channels[1])
    const c_2=prepareChannel(channels[2])
    
    const octave_offset = Math.max(
      getOffset(c_0),getOffset(c_1),getOffset(c_2),
    )
    if(octave_offset > 0){
      console.warn(`Octave Offset: ${octave_offset}`)
    }
    
    // const octave_offset = 2
    
    const c_0_r = padChannel(c_0, octave_offset)
    const c_1_r = padChannel(c_1, octave_offset)
    const c_2_r = padChannel(c_2, octave_offset)
    
    const p_bucket=[]
    let p_temp=[]
    
    let p_max = Math.max(c_0_r.length, c_1_r.length, c_2_r.length)
    // p_max = Math.ceil(p_max/256) * 256
    
    for(let i=0;i<p_max;i++){
      if(i%64==0 && i>0){
        p_bucket.push(p_temp)
        p_temp=[]
      }
      const p1 = c_0_r[i] || nullCell()
      const p2 = c_1_r[i] || nullCell()
      const p3 = c_2_r[i] || nullCell()
      
      if(p3 && p3.instrument) p3.instrument=10
        
      p_temp.push([p1, p2, p3, nullCell()])
    }
    
    return p_bucket
}
song.patterns = convertNsfToUgePattern(nsf)
song.sequence = Array(song.patterns.length).fill(0).map((x,i)=>i)
song.ticks_per_row = 4 // This should actually pull from the BeatLength value
const buff = saveUGESong(song)
writeFileSync("prolog_gb.uge", new Uint8Array(buff), "utf8")
