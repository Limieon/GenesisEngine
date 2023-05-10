import FS from 'fs'
import Path from 'path'
import Chalk from 'chalk'

function deleteFilesWithExtensionInFolders(folders, extensions) {
	folders.forEach((folder) => {
		if (!FS.existsSync(folder)) {
			console.log(Chalk.red(`Folder: ${Chalk.magenta(file)} does not exist!`))
			return
		}
		const files = getAllFilesInDirectory(folder)

		files.forEach((file) => {
			const fileName = Path.basename(file)
			extensions.forEach(e => {
				if (fileName.endsWith(e)) {
					console.log(Chalk.gray(`Deleting file: ${Chalk.magenta(file)}...`))
					FS.unlinkSync(file)
				}
			})
		})
	})
}

function getAllFilesInDirectory(directoryPath, arrayOfFiles) {
	const files = FS.readdirSync(directoryPath)

	arrayOfFiles = arrayOfFiles || []

	files.forEach((file) => {
		const fullPath = Path.join(directoryPath, file)
		if (FS.statSync(fullPath).isDirectory()) {
			arrayOfFiles = getAllFilesInDirectory(fullPath, arrayOfFiles)
		} else {
			arrayOfFiles.push(fullPath)
		}
	})

	return arrayOfFiles
}

console.log(Chalk.gray('Cleaning...'))
deleteFilesWithExtensionInFolders(['Genesis', 'Runtime', 'ThirdParty'], ['.vcxproj', '.vcxproj.user', '.vcxproj.filters'])
if (FS.existsSync('GenesisEngine.sln')) FS.unlinkSync('GenesisEngine.sln')

console.log(Chalk.gray(`Deleting Directory: ${Chalk.magenta('./bin/')}...`))
FS.rmSync('./bin', { recursive: true })
console.log(Chalk.gray(`Deleting Directory: ${Chalk.magenta('./bin-int/')}...`))
FS.rmSync('./bin-int', { recursive: true })

console.log(Chalk.green('Done!'))
