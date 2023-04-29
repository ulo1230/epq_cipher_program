const fs = require("fs");
const utils = require("/share/Servers/Main/utils");

const handleRequest = (request, response) => {
	switch(request.path.root) {
		case "/": {
			response.writeHead(302, { "Location": "/cipher/index.html" });
			response.end();
		} break;

		default: {
			const resource = decodeURIComponent(request.path.splice(0).join("/"));

			try {
				const data = fs.readFileSync(__dirname + "/" + resource);
				response.writeHead(200, {
					"Content-Type": utils.mimeType(resource),
					"Content-Length": data.length,
					"Access-Control-Allow-Origin": "*"
				});
				response.write(data);
			} catch(e) {
				response.writeHead(404);
			}

			response.end();
		} break;
	}
};

module.exports = { handleRequest };
