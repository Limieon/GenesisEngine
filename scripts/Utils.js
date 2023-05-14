import { spawn, exec, execFile } from 'child_process'

import Chalk from 'chalk'

export default class Utils {
	static async executeCommand(cmd, args) {
		//console.log(Chalk.magenta(cmd), Chalk.gray(args.join(' ')))
		return new Promise((res, rej) => {
			const cprocess = spawn(cmd, args, { stdio: 'inherit' })

			cprocess.on('exit', (code, signal) => {
				res({ code, signal })
			})
		})
	}

	static async executeFile(file, args) {
		console.log(Chalk.magenta(file), Chalk.gray(args.join(' ')))
		return new Promise((res, rej) => {
			const cprocess = execFile(file, args, (e, stdout, stderr) => {
				if (e) console.log(e)
			})
			cprocess.stdout.pipe(process.stdout)
			cprocess.stderr.pipe(process.stderr)
			process.stdin.pipe(cprocess.stdin)

			cprocess.on('exit', (code, signal) => {
				res({ code, signal })
			})
		})
	}
}
