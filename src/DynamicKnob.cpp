#include "ValleyWidgets.hpp"

DynamicKnob::DynamicKnob() {
    fb = new widget::FramebufferWidget;
	addChild(fb);

	shadow = new CircularShadow;
	fb->addChild(shadow);
	shadow->box.size = math::Vec();

	tw = new widget::TransformWidget;
	fb->addChild(tw);

	sw = new widget::SvgWidget;
	tw->addChild(sw);

    _visibility = nullptr;
    _viewMode = ACTIVE_HIGH_VIEW;
}

void DynamicKnob::setSvg(std::shared_ptr<SVG> svg) {
	sw->svg = svg;
	sw->wrap();
	tw->box.size = sw->box.size;
	box.size = sw->box.size;
    shadow->box.size = sw->box.size;
	shadow->box.pos = Vec(0, sw->box.size.y * 0.1);
}

/*void DynamicKnob::step() {
	// Re-transform TransformWidget if dirty
    if(_visibility != nullptr) {
        if(*_visibility) {
            visible = true;
        }
        else {
            visible = false;
        }
        if(_viewMode == ACTIVE_LOW_VIEW) {
            visible = !visible;
        }
    }
    else {
        visible = true;
    }
	fb->step();
}*/

/*void DynamicKnob::onChange(const event::Change &e) {
	if (paramQuantity) {
		float angle;
		if (paramQuantity->isBounded()) {
			angle = math::rescale(paramQuantity->getScaledValue(), 0.f, 1.f, minAngle, maxAngle);
		}
		else {
			angle = math::rescale(paramQuantity->getValue(), -1.f, 1.f, minAngle, maxAngle);
		}
		angle = std::fmod(angle, 2*M_PI);
		tw->identity();
		// Rotate SVG
		math::Vec center = sw->box.getCenter();
		tw->translate(center);
		tw->rotate(angle);
		tw->translate(center.neg());
		fb->dirty = true;
	}
	Knob::onChange(e);
}*/

////////////////////////////////////////////////////////////////////////////////

DynamicSvgKnob::DynamicSvgKnob() {
    _visibility = nullptr;
    _viewMode = ACTIVE_HIGH_VIEW;
}

void DynamicSvgKnob::step() {
    if(_visibility != nullptr) {
        if(*_visibility) {
            visible = true;
        }
        else {
            visible = false;
        }
        if(_viewMode == ACTIVE_LOW_VIEW) {
            visible = !visible;
        }
    }
    else {
        visible = true;
    }
    if (paramQuantity) {
		float value = paramQuantity->getValue();
		// Trigger change event when paramQuantity value changes
		if (value != dirtyValue) {
			dirtyValue = value;
			event::Change eChange;
			onChange(eChange);
		}
	}

	Widget::step();
}
