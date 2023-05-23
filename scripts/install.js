import FS from 'fs'
import Chalk from 'chalk'

import Utils from './Utils.js'

const modules = {
	spdlog: 'https://github.com/GMasterHD/spdlog',
	fmt: 'https://github.com/fmtlib/fmt',
	glad: 'https://github.com/GMasterHD/glad',
	glfw: 'https://github.com/glfw/glfw',
	glm: 'https://github.com/g-truc/glm',
	imgui: 'https://github.com/ocornut/imgui;docking',
	stb: 'https://github.com/nothings/stb'
}

console.log(Chalk.gray('Installing modules...'))
for (const m of Object.keys(modules)) {
	const url = modules[m]

	if (FS.existsSync(`ThirdParty/${m}`)) {
		console.log(Chalk.yellow(`Skipping ${Chalk.magenta(m)} because directory already exists!`))
		continue
	}

	if (url.includes(';')) {
		const split = url.split(';')

		await Utils.executeCommand('git', ['clone', '-b', split[1], split[0], `ThirdParty/${m}`])
		continue
	}

	await Utils.executeCommand('git', ['clone', url, `ThirdParty/${m}`])
}
console.log(Chalk.green('Done!'))
