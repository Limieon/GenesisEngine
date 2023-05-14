import FS from 'fs'
import Chalk from 'chalk'

import Utils from './Utils.js'

const modules = {
	spdlog: "https://github.com/Gabime/spdlog",
	fmt: "https://github.com/fmtlib/fmt"
}

console.log(Chalk.gray('Installing modules...'))
for (const m of Object.keys(modules)) {
	const url = modules[m]

	if (FS.existsSync(`ThirdParty/${m}`)) {
		console.log(Chalk.yellow(`Skipping ${Chalk.magenta(m)} because directory already exists!`))
		continue
	}

	await Utils.executeCommand('git', ['clone', url, `ThirdParty/${m}`])
}
console.log(Chalk.green('Done!'))
