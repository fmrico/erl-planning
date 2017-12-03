(define (domain attending_visitors)

(:requirements :strips :typing :fluents :disjunctive-preconditions :durative-actions)

(:types
	robot
	doctor
	bell
)

(:predicates
	(robot_ready ?r - robot)
	(bell_ringed ?b - bell)
	(doctor_recognized)
	(deli_recognized)
	(visitor_attended)
)

(:durative-action attend_deli
	:parameters ()
	:duration ( = ?duration 10)
	:condition (and
		(over all(deli_recognized))
		)
	:effect (and
		(at end(visitor_attended))
		)
)

(:durative-action attend_doctor
	:parameters ()
	:duration ( = ?duration 10)
	:condition (and
		(over all(doctor_recognized))
		)
	:effect (and
		(at end(visitor_attended))
		)
)

(:durative-action recognize_person
	:parameters (?b - bell)
	:duration ( = ?duration 10)
	:condition (and
		(at start (bell_ringed ?b))
		)
	:effect (and
		(at end(doctor_recognized))
		(at end(deli_recognized))
		)
)

(:durative-action wait_bell
	:parameters (?b - bell ?r - robot)
	:duration ( = ?duration 10)
	:condition (and
		(over all(robot_ready ?r))
		)
	:effect (and
		(at end(bell_ringed ?b))
		)
)
)
