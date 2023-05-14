import Path from 'path'
import Chalk from "chalk"
import FS from 'fs'

import Utils from "../Utils.js"

const originWD = process.cwd()

const args = process.argv.slice(2)
const [config, architecture] = args

const BX_DIR = Path.join(process.cwd(), 'ThirdParty', 'bx')
const BIMG_DIR = Path.join(process.cwd(), 'ThirdParty', 'bimg')
const BGFX_DIR = Path.join(process.cwd(), 'ThirdParty', 'bgfx')
const OUT_PATH = Path.join(originWD, 'lib', process.platform, `${config}-${architecture}`)

if (!FS.existsSync(OUT_PATH)) FS.mkdirSync(OUT_PATH, { recursive: true })


console.log(Chalk.gray('Adding genie to path...'))
switch (process.platform) {
	case 'win32': {
		process.env.PATH = `${Path.join(BX_DIR, 'tools/bin/windows/')};${process.env.PATH}`
		break
	}

	case 'linux': {
		console.log(Chalk.red(`${Chalk.magenta('Linux')} is currently not supported!`))
		break
	}

	case 'darwin': {
		console.log(Chalk.red(`${Chalk.magenta('Darwin')} is currently not supported!`))
		break
	}
}

console.log(Chalk.gray(`Building ${Chalk.magenta('bx')}...`))
process.chdir(BX_DIR)

switch (process.platform) {
	case 'win32': {
		await Utils.executeCommand('genie.exe', ['vs2022'])

		process.chdir('./.build/projects/vs2022/')

		await Utils.executeCommand('MSBuild.exe', ['bx.vcxproj', `/p:Configuration=${config}`, `/p:Platform=${architecture}`])

		FS.cpSync('../../win64_vs2022/bin/bxDebug.lib', Path.join(OUT_PATH, 'bx.lib'))

		break
	}

	case 'linux': {
		console.log(Chalk.red(`${Chalk.magenta('Linux')} is currently not supported!`))
		break
	}

	case 'darwin': {
		console.log(Chalk.red(`${Chalk.magenta('Darwin')} is currently not supported!`))
		break
	}
}

console.log(Chalk.gray(`Building ${Chalk.magenta('bimg')}...`))
process.chdir(BIMG_DIR)

switch (process.platform) {
	case 'win32': {
		await Utils.executeCommand('genie.exe', ['vs2022'])

		process.chdir('./.build/projects/vs2022/')

		await Utils.executeCommand('MSBuild.exe', ['bimg.vcxproj', `/p:Configuration=${config}`, `/p:Platform=${architecture}`])

		FS.cpSync('../../win64_vs2022/bin/bimgDebug.lib', Path.join(OUT_PATH, 'bimg.lib'))

		break
	}

	case 'linux': {
		console.log(Chalk.red(`${Chalk.magenta('Linux')} is currently not supported!`))
		break
	}

	case 'darwin': {
		console.log(Chalk.red(`${Chalk.magenta('Darwin')} is currently not supported!`))
		break
	}
}

console.log(Chalk.gray(`Building ${Chalk.magenta('bgfx')}...`))
process.chdir(BGFX_DIR)

switch (process.platform) {
	case 'win32': {
		await Utils.executeCommand('genie.exe', ['vs2022'])

		process.chdir('./.build/projects/vs2022/')

		await Utils.executeCommand('MSBuild.exe', ['bgfx.vcxproj', `/p:Configuration=${config}`, `/p:Platform=${architecture}`])

		FS.cpSync('../../win64_vs2022/bin/bgfxDebug.lib', Path.join(OUT_PATH, 'bgfx.lib'))

		break
	}

	case 'linux': {
		console.log(Chalk.red(`${Chalk.magenta('Linux')} is currently not supported!`))
		break
	}

	case 'darwin': {
		console.log(Chalk.red(`${Chalk.magenta('Darwin')} is currently not supported!`))
		break
	}
}

process.chdir(originWD)

console.log(Chalk.green('Done!'))
