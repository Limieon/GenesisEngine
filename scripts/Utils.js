import { spawn } from 'child_process'

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
}
