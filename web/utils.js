const $ = (selector, el) => { return (el || document).querySelector(selector); };
const $$ = (selector, el) => { return (el || document).querySelectorAll(selector); };
const $id = (id, el) => { return (el || document).getElementById(id) };
const $tag = (tag, el) => { if(!el) el = document; return el.getElementsByTagName(tag) };
const $class = (cls, el) => { if(!el) el = document; return el.getElementsByClassName(cls); };

function $get(uri) {
	return new Promise((accept, reject) => {
		const req = new XMLHttpRequest;
		req.open("GET", uri);
		req.addEventListener("load", () => { if(req.status == 200) accept(req.response) });
		req.addEventListener("error", (e) => reject(e));
		req.send();
	});
}

function $post(uri, data) {
	return new Promise((accept, reject) => {
		const req = new XMLHttpRequest;
		req.open("POST", uri);
		req.addEventListener("load", () => { if(req.status == 200) accept(req.response) });
		req.addEventListener("error", (e) => reject(e));
		req.send(data);
	});
}

const htmlToElement = (html) => {
	let el = document.createElement("div");
	el.innerHTML = html.trim();
	return el.firstChild;
};