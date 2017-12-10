(define (domain attending_visitors)

(:requirements :strips :typing :equality :fluents :disjunctive-preconditions :durative-actions :negative-preconditions)

(:types
	location
	object
	visitor
	host
	bell
	robot
)

(:predicates
	(mission_accomplished ?r - robot)

	(food_delivered ?p - visitor)
	(host_attended ?h - host ?p - visitor)

	(bedroom_location ?l - location)
	(entrance_location ?l - location)
	(kitchen_location ?l - location)
	(start_location ?l - location)

	(robot_at ?r - robot ?l - location)
	(person_at ?p - visitor ?l - location)

	(visitor_attended ?p - visitor)
	(recognized ?p - visitor)

	(deli_person ?p - visitor)
	(doctor_person ?p - visitor)

	(bell_ringed ?b - bell)
)



(:action accomplish_mission
	:parameters (?r - robot ?p - visitor ?l1 ?l2 - location)
	:precondition (and
		(robot_at ?r ?l1)
		(person_at ?p ?l2)
		(entrance_location ?l2)
		(start_location ?l1)
		(visitor_attended ?p)
		)
	:effect(and
		(mission_accomplished ?r)
	)
)

(:action attend_doctor
	:parameters (?h - host ?p - visitor)
	:precondition (and
		(host_attended ?h ?p)
	)
	:effect(and
		(visitor_attended ?p)
	)
)

(:action attend_deli
	:parameters (?r - robot ?p - visitor ?l - location)
	:precondition (and
		(food_delivered ?p)
	)
	:effect(and
		(visitor_attended ?p)
	)
)

(:durative-action recognize_person
	:parameters (?r - robot ?p - visitor ?l - location ?b - bell)
	:duration ( = ?duration 10)
	:condition (and
		(at start(bell_ringed ?b))
		(over all(robot_at ?r ?l))
		(over all(entrance_location ?l))
		(over all(person_at ?p ?l))
	)
	:effect(and
		(at end(recognized ?p))
		(at end(not(bell_ringed ?b)))
	)
)

(:durative-action attend_Annie
	:parameters (?h - host ?r - robot ?p - visitor ?l - location)
	:duration ( = ?duration 10)
	:condition (and
		(over all(person_at ?p ?l))
		(over all(bedroom_location ?l))
		(over all(doctor_person ?p))
		(over all(recognized ?p))
	)
	:effect(and
		(at end(host_attended ?h ?p))
	)
)

(:durative-action deliver_food
	:parameters (?r - robot ?p - visitor ?l - location)
	:duration ( = ?duration 10)
	:condition (and
		(over all(person_at ?p ?l))
		(over all(kitchen_location ?l))
		(over all(deli_person ?p))
		(over all(recognized ?p))
	)
	:effect(and
		(at end(food_delivered ?p))
	)
)

(:durative-action escort_to
	:parameters (?r - robot ?p - visitor ?l1 ?l2 - location)
	:duration ( = ?duration 10)
	:condition (and
		(at start(not(= ?l1 ?l2)))
		(at start(robot_at ?r ?l1))
		(at start(person_at ?p ?l1))
		(over all(recognized ?p))
	)
	:effect(and
		(at end (robot_at ?r ?l2))
		(at end (person_at ?p ?l2))
		(at end (not (person_at ?p ?l1)))
		(at end (not (robot_at ?r ?l1)))
	)
)

(:durative-action move_to
	:parameters (?r - robot ?l1 ?l2 - location)
	:duration ( = ?duration 5)
	:condition (and
		(at start(not(= ?l1 ?l2)))
		(at start(robot_at ?r ?l1))
	)
	:effect(and
		(at end (robot_at ?r ?l2))
		(at end (not (robot_at ?r ?l1)))
	)
)

)
