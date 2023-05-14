import FS from 'fs'
import Chalk from 'chalk'

import Utils from './Utils.js'

const modules = {
	spdlog: "https://github.com/Gabime/spdlog",
	fmt: "https://github.com/fmtlib/fmt",
	bx: "https://github.com/bkaradzic/bx",
	bimg: "https://github.com/bkaradzic/bimg",
	bgfx: "https://github.com/bkaradzic/bgfx",
	glfw: "https://github.com/glfw/glfw",
	glm: "https://github.com/g-truc/glm"
}

console.log(Chalk.gray('Installing modules...'))
for (const m of Object.keys(modules)) {
	const url = modules[m]

	if (FS.existsSync(`ThirdParty/${m}`)) {
		console.log(Chalk.yellow(`Skipping ${Chalk.magenta(m)} because directory already exists!`))
		continue
	}

	console.log(Chalk.gray(`Cloning ${Chalk.magenta(url)} into ${Chalk.cyan(`ThirdParty/${m}`)}`))
	await Utils.executeCommand('git', ['clone', url, `ThirdParty/${m}`])
}
console.log(Chalk.green('Done!'))
