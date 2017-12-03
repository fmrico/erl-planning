(define (domain balls_boxes)

(:requirements :strips :typing :fluents :disjunctive-preconditions :durative-actions)

(:types
	ball
	box
	arm
	bell
)

(:constants
	(red - ball)
	(blue - ball)
	(A - box)
	(B - box)
	(C - box)
	(army - arm)
	(belly - bell)
)

(:predicates
	(ball_at_box ?bl - ball ?bx - box)
	(arm_at_box ?bl - ball ?bx - box)
	(covered ?bx - box)
	(free ?bx - box)
	(available ?a - arm)
	(activated ?b - bell)
)

(:durative-action move_arm
	:parameters (?a - arm ?from ?to - box ?)
	:duration ( = ?duration 10)
	:condition (and
		(at start (arm_at_box ?a ?from))
		(at start (available ?to)))
	:effect (and
		(at end (arm_at_box ?a ?to))
		(at end (not (arm_at_box ?a ?from)))
		)
)

(:durative-action remove_cover
	:parameters (?a - arm ?b - box ?)
	:duration ( = ?duration 10)
	:condition (and
		(at start (arm_at_box ?a ?b))
		(at start (covered ?b)))
	:effect (and
		(at end (not (covered ?b)))
		)
)

(:durative-action move_ball
	:parameters (?b - ball ?from ?to - box ?)
	:duration ( = ?duration 10)
	:condition (or
			(and
				(over all(=(?b red)))
				(over all(=(?to B)))
				(at start (ball_at_box ?b ?from))
				(over all (free ?to))
				(at start (not (covered ?from)))
				(at start (not (covered ?to)))
			)
			(and
				(over all(=(?b blue)))
				(over all(=(?to C)))
				(at start (ball_at_box ?b ?from))
				(over all (free ?to))
				(at start (not (covered ?from)))
				(at start (not (covered ?to)))
			)
		)
	:effect (and
		(at end (ball_at_box ?b ?to))
		(at end (not (ball_at_box ?b ?from)))
		(at end (covered ?from))
		(at end (covered ?to))
		)
)
)
