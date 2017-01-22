import { Component } from "@angular/core";

@Component({
	selector: "drone-cockpit",
	templateUrl: "pages/cockpit/cockpit.html",
	styleUrls: ["pages/cockpit/cockpit.common.css"]
})
export class CockpitComponent {

	constructor() {
		//debug
		console.info("Welcome to your cockpit pilot ;)");
	}
}