import FS from 'fs'
import Path from 'path'
import Chalk from 'chalk'
import { spawn } from 'child_process'

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

	await new Promise((res, rej) => {
		console.log(Chalk.gray(`Installing ${Chalk.magenta(m)}...`))

		const cprocess = spawn('git', ['clone', url, `ThirdParty/${m}`])
		cprocess.stdout.pipe(process.stdout)
		cprocess.stderr.pipe(process.stderr)
		process.stdin.pipe(cprocess.stderr)

		cprocess.on('exit', e => {
			res()
		})
	})
}
console.log(Chalk.green('Done!'))
