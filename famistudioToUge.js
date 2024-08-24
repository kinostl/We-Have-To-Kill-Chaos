import {
  exportToC,
  loadUGESong,
  saveUGESong,
} from "shared/lib/uge/ugeHelper";
import { noteStringsForClipboard } from "shared/lib/music/constants";
import { readFileSync, writeFileSync } from "fs-extra";

const data = readFileSync(`./song_template_v6.uge`);
const nsf = readFileSync(`./ff1_cornelia_famistudio.txt`, 'utf-8');

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

const nullCell = {
  instrument: null,
  note: null,
  effectcode: null,
  effectparam: null
}

function convertToCell(cell){
  if(!cell || !cell.Value) return nullCell
    if(cell.Value.length == 2){
      cell.Value = `${cell.Value[0]}-${cell.Value[1]}`
    }
  const out = {
    instrument: instrumentMap[cell.Instrument] || null,
    note: noteStringsForClipboard.indexOf(cell.Value),
    effectcode: null,
    effectparam: null
  }
  
  if(out.note < 0) out.note = null
  
    return out
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
    
    const c_0=channels[0].map(convertToCellsObject).map((x)=>{
      x.note_index = parseInt(x["Note Time"])
      x.note_index += (n_i * 256)
      if(x["Note Time"] == 255){
        n_i++
      }
      
      return x
    })
    
    n_i=0;
    const c_1=channels[1].map(convertToCellsObject).map((x)=>{
      x.note_index = parseInt(x["Note Time"])
      x.note_index += (n_i * 256)
      if(x["Note Time"] == 255){
        n_i++
      }
      
      return x
    })

    const c_0_r = c_0.reduce((arr, x)=>{
      while(arr.length < x.note_index){
        arr.push(nullCell)
      }
      arr.push(convertToCell(x))
      return arr
    },[]).filter((x)=>{
      return Object.values(x).some(y=>y!=null)
    })
    
    
    
    const c_1_r = c_1.reduce((arr, x)=>{
      while(arr.length < x.note_index){
        arr.push(nullCell)
      }
      arr.push(convertToCell(x))
      return arr
    },[]).filter((x)=>{
      return Object.values(x).some(y=>y!=null)
    })
    
    
    const c_2=channels[2].map(convertToCellsObject).map((x)=>{
      x.note_index = parseInt(x["Note Time"])
      x.note_index += (n_i * 256)
      if(x["Note Time"] == 255){
        n_i++
      }
      
      return x
    })
    
        
    const c_2_r = c_2.reduce((arr, x)=>{
      while(arr.length < x.note_index){
        arr.push(nullCell)
      }
      arr.push(convertToCell(x))
      return arr
    },[]).filter((x)=>{
      return Object.values(x).some(y=>y!=null)
    })
    
    const p_bucket=[]
    let p_temp=[]
    
    const p_max = Math.max(c_0_r.length, c_1_r.length)
    
    
    for(let i=0;i<p_max;i++){
      if(i%32==0 && i>0){
        p_bucket.push(p_temp)
        p_temp=[]
      }
      const p1 = c_0_r[i] || nullCell
      const p2 = c_1_r[i] || nullCell
      const p3 = c_2_r[i] || nullCell
      
      if(p3 && p3.instrument) p3.instrument=10
        
      p_temp.push([p1, p2, p3, nullCell])
      p_temp.push([nullCell, nullCell, nullCell, nullCell])
    }
    
    return p_bucket
}
song.patterns = convertNsfToUgePattern(nsf)
song.sequence = Array(song.patterns.length).fill(0).map((x,i)=>i)
const buff = saveUGESong(song)
writeFileSync("cornelia.uge", new Uint8Array(buff), "utf8")
