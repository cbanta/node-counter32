{
	"targets": [
		{
			"target_name": "counter32",
			"sources": [
				"src/counter32.cc"
			],
			"include_dirs" : [
 	 			"<!(node -e \"require('nan')\")"
			]
		}
	]
}
