import FS from 'fs'
import Path from 'path'

// Config
const regex = /includeDirs\["(.*?)"]\s*=\s*"(.*?)"/gm;

const dependenciesFile = "dependencies.lua"
const settingsFile = '.vscode/c_cpp_properties.json'

const dependencies = FS.readFileSync(dependenciesFile, { encoding: "utf-8" })
const settings = JSON.parse(FS.readFileSync(settingsFile, { encoding: 'utf-8' }))

let m
while ((m = regex.exec(dependencies)) !== null) {
    if (m.index === regex.lastIndex) {
        regex.lastIndex++;
    }

    const [lib, path] = m.slice(1)
    if (lib === 'Genesis' || lib === 'Runtime') continue

    for (let cfg of settings.configurations) {
        const p = path.replace('%{wks.location}', '${workspaceFolder}') + '**'
        if (!cfg.includePath.includes(p)) {
            cfg.includePath.push(p)
        }
    }
}

FS.writeFileSync(settingsFile, JSON.stringify(settings, null, 4))
