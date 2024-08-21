const test_string=`Project Version="4.2.1" TempoMode="FamiStudio" Name="Final Fantasy 1" Author="Nobuo Uematsu" Copyright="1987 Square"
	Instrument Name="Duty 0" Color="7b8df1"
	Instrument Name="Duty 1" Color="ffffb2"
		Envelope Type="DutyCycle" Length="1" Values="1"
	Song Name="Song 1" Color="d863ec" Length="29" LoopPoint="0" PatternLength="32" BeatLength="4" NoteLength="8" Groove="8" GroovePaddingMode="Middle"
		Channel Type="Square1"
			Pattern Name="Pattern 1" Color="8a706a"
				Note Time="0" Value="A#4" Duration="8" Instrument="Duty 1" Volume="14" FinePitch="1"
				Note Time="1" Volume="12"
				Note Time="2" Volume="11"
				Note Time="3" Volume="9"
				Note Time="4" Volume="8"
				Note Time="5" Volume="6"
				Note Time="6" Volume="5"
				Note Time="7" Volume="3"`

function convertNsfToUgePattern(nsf_file){
    let current_pattern = -1
    const nsf_rows = nsf_file.split('\n').map((x)=>x.trim()).reduce((rows, row) => {
        if (row.startsWith("Pattern")) {
            current_pattern++;
            rows[current_pattern]=[]
        }
        if (row.startsWith("Note")) {
            rows[current_pattern].push(row.trim())
        }
        return rows
    }, [])
    
    const patterns = nsf_rows.map((nsf_row) => {
        const rows = nsf_row.map((pattern_row) => {
            const cells = pattern_row.split("\" ")
            const props = cells.map((cell) => cell.trim().split("="))
            return props.reduce((prop_obj, x) => {
                prop_obj[x[0]] = x[1].replaceAll("\"","")
                return prop_obj
            }, {})
        })
        return rows.filter((x)=>(x.Value && x.Instrument)).map((x)=>({
            instrument: x.Instrument,
            note: x.Value,
            effectcode: null,
            effectparam: null
        }))
    })

    return patterns
}